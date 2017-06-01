/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_fixed_mempool.c
 *
 *	@brief	Windows版 iTRONサービスコール (固定長メモリプール).
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_fixed_mempool.h"

/****************************************************************************
 *
 * ローカル関数定義.
 *
 ****************************************************************************/
static BYTE	*GetFreeMem( WIMPFOBJ *mpf, INT tskid );
static void	ReleaseFreeMem( WIMPFOBJ *mpf, WIHDR* blk );
static void	MemAllocWaitTask( WIMPFOBJ *mpf );

/****************************************************************************
 *
 * ローカル変数定義.
 *
 ****************************************************************************/
static WIHDR	*ObjList;			//!< 固定長メモリプール･リストのポインタ.

/****************************************************************************/
/*!
 *	@brief	固定長メモリプールの初期処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_InitFixedMemPool( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	固定長メモリプールの終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_QuitFixedMemPool( void )
{
	WIHDR		*next_ptr;
	WIMPFOBJ	*p = (WIMPFOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! メモリバッファを解放する.
		SAFE_RELEASE( p->MemBuf );

		//! 固定長メモリプール･オブジェクト構造体を解放する.
		SAFE_RELEASE( p );

		//! 次のメモリプール･オブジェクト構造体を取り出す.
		p = (WIMPFOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	固定長メモリプールの生成.
 *
 *	@param	[in]	id		メモリプールID番号.
 *	@param	[in]	obj		メモリプール･オブジェクト構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_CreateFixedMemPool( INT id, const WIMPFOBJ *obj )
{
	INT			i;
	DWORD		size;
	WIHDR		*ptr;
	ER			ercd;
	WIMPFOBJ	*p;

	//! 固定長メモリプール･オブジェクトを作成する.
	p = (WIMPFOBJ *)wi_CreateObject( id, TMAX_MAXMPF, sizeof(WIMPFOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 引数が不正な場合はエラーにする.
	if( obj->BlockCnt <= 0 || obj->BlockSize <= 0 ){
		return E_PAR;
	}
	//! メモリブロックの1ブロックのサイズを計算する.
	size = obj->BlockSize + sizeof(WIHDR);

	//! メモリプールのバッファを確保する.
	p->MemBuf = (BYTE*)malloc( obj->BlockCnt * size );
	if( !p->MemBuf ){
		SAFE_RELEASE( p );
		return E_NOMEM;
	}
	//! 確保したバッファをクリアする.
	memset( p->MemBuf, 0, obj->BlockCnt * size );

	//! 未使用メモリブロックキューにバッファを登録する.
	ptr = (WIHDR *)(p->MemBuf);
	for( i = 0; i < obj->BlockCnt - 1; i++ ){
		ptr->Next = (WIHDR *)((DWORD)ptr + size);
		ptr       = (WIHDR *)((DWORD)ptr + size);
	}
	p->FreeQue = (WIHDR *)(p->MemBuf);
	p->UsedQue = NULL;
	p->WaitQue = NULL;

	//! リストに固定長メモリプールを追加する.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	固定長メモリプールの削除.
 *
 *	@param	[in]	id		メモリプールID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_DeleteFixedMemPool( INT id )
{
	ER			ercd;
	WIMPFOBJ	*p;

	//! メモリプールIDのオブジェクトを取得する.
	p = (WIMPFOBJ *)wi_FindObject( id, TMAX_MAXMPF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストから該当するメモリプールを取り除く.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! 待ちタスクキューを解放する.
	wi_WakeupDelResource( p->WaitQue );

	//! メモリプールのバッファを解放する.
	SAFE_RELEASE( p->MemBuf );

	//! 固定長メモリプール･オブジェクト構造体を解放する.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	固定長メモリブロックの獲得.
 *
 *	@param	[in]	id		メモリプールID番号.
 *	@param	[out]	buf		メモリブロックのアドレスを格納する領域のポインタ.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		wi_GetFixedMemPool( INT id, VP buf, TMO tmout )
{
	ER			ercd;
	WIMPFOBJ	*p;
	WITSKOBJ	*tsk;
	BYTE		*blk;

	//! メモリプールIDのオブジェクトを取得する.
	p = (WIMPFOBJ *)wi_FindObject( id, TMAX_MAXMPF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 引数が不正な場合はエラーにする.
	if( !buf ){
		return E_PAR;
	}
	//! タスク以外からの呼び出しの場合はエラーにする.
	tsk = wi_GetTaskObject( TSK_SELF );
	if( !tsk ){
		return E_CTX;
	}
	//! 未使用のメモリブロックを取得する.
	blk = GetFreeMem( p, tsk->Hdr.Id );

	//! 未使用のメモリブロックがない場合、メモリブロックが返却されるまでタスクをスリープさせる.
	if( !blk ){
		ercd = wi_TaskWait( id, TTW_MPF, tmout, p->Attribute, &(p->WaitQue) );
		if( ercd != E_OK ){
			return ercd;
		}
		blk = tsk->Param[0];
	}
	//! 貸し出すメモリブロックからリンクヘッダを削除する.
	*((DWORD *)buf) = (DWORD)blk;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	固定長メモリブロックの返却.
 *
 *	@param	[in]	id		メモリプールID番号.
 *	@param	[in]	buf		返却するメモリブロックのアドレス.
 *
 *	@retval	エラーコード.
 */
ER		wi_ReleaseFixedMemPool( INT id, VP buf )
{
	ER			ercd;
	WIMPFOBJ	*p;
	WIHDR		*blk,*ptr;

	//! メモリプールIDのオブジェクトを取得する.
	p = (WIMPFOBJ *)wi_FindObject( id, TMAX_MAXMPF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 引数が不正な場合はエラーにする.
	if( !buf ){
		return E_PAR;
	}
	//! 返却されたアドレスからメモリブロックのヘッダ部のアドレスを計算する.
	blk = (WIHDR *)((DWORD)buf - sizeof(WIHDR) );

	//! 貸し出し中メモリブロックキューに返却されたメモリブロックがあるかどうかを調べる.
	for( ptr = p->UsedQue; ptr && ptr != blk; ptr = ptr->Next ) ;
	if( !ptr ){
		return E_OBJ;
	}
	//! 返却されたメモリブロックを解放する.
	ReleaseFreeMem( p, blk );

	//! メモリブロック獲得待ちのタスクがある場合、メモリブロックを貸し出してタスクを起床する.
	MemAllocWaitTask( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	固定長メモリプールの参照.
 *
 *	@param	[in]	id		メモリプールID番号.
 *	@param	[out]	sts		メモリプール状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_RefarenceFixedMemPool( INT id, WIMPFSTAT *sts )
{
	ER			ercd;
	WIMPFOBJ	*p;
	WIHDR		*ptr;
	INT			cnt;

	//! メモリプールIDのオブジェクトを取得する.
	p = (WIMPFOBJ *)wi_FindObject( id, TMAX_MAXMPF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 未使用のメモリブロック数をカウントする.
	cnt = 0;
	ptr = p->FreeQue;
	while( ptr ){
		ptr = ptr->Next;
		cnt++;
	}
	//! 固定長メモリプールの状態を構造体にセットする.
	sts->WaitId    = wi_GetWaitTaskListFirstId( p->WaitQue );
	sts->FreeBlock = cnt;
	sts->ExtInfo   = p->ExtInfo;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	削除されるタスクが確保したメモリブロックを解放する.
 *
 *	@param	[in]	id		削除されるタスクID番号.
 *
 *	@retval	なし.
 */
void	wi_AllReleaseFixedMemPool( INT id )
{
	WIHDR		*ptr;
	WIMPFOBJ	*p = (WIMPFOBJ *)ObjList;

	while( p ){
		//! 貸し出し中メモリブロックキューに削除されるタスクに貸し出したメモリがあるかどうかを調べる.
		ptr = p->UsedQue;
		while( ptr ){
			WIHDR *next_ptr;
			next_ptr = ptr->Next;

			//! 貸し出したメモリがあった場合、貸し出したメモリを解放する.
			if( ptr->Id == id ){
				ReleaseFreeMem( p, ptr );
			}
			ptr = next_ptr;
		}
		//! 待ち行列から消滅するタスクを削除する.
		if( p->WaitQue ){
			p->WaitQue = wi_DelWaitTaskList( id, p->WaitQue );
		}
		//! メモリブロック獲得待ちのタスクがある場合、メモリブロックを貸し出してタスクを起床する.
		MemAllocWaitTask( p );

		//! 次のメモリプール構造体をを取り出す.
		p = (WIMPFOBJ *)(p->Hdr.Next);
	}
}

/****************************************************************************/
/*!
 *	@brief	空いているメモリブロックを取得する.
 *
 *	@param	[in]	mpf		固定長メモリプール･オブジェクトのポインタ.
 *	@param	[in]	tskid	メモリを取得するタスクのID.
 *
 *	@retval	取得したメモリブロックのポインタ.
 */
static BYTE	*GetFreeMem( WIMPFOBJ *mpf, INT tskid )
{
	WIHDR *blk,*ptr;

	if( !mpf->FreeQue ){
		return NULL;
	}
	//! 貸し出すメモリブロックを未使用メモリブロックキューの先頭から取り出す.
	blk = mpf->FreeQue;

	//! 未使用メモリブロックキューの先頭から貸し出したメモリブロックを削除する.
	mpf->FreeQue = mpf->FreeQue->Next;

	//! 貸し出し中メモリブロックキューに貸し出したメモリブロックを追加する.
	if( !mpf->UsedQue ){
		mpf->UsedQue = blk;
	}else{
		for( ptr = mpf->UsedQue; ptr->Next; ptr = ptr->Next ) ;
		ptr->Next = blk;
	}
	blk->Next = NULL;
	blk->Id   = tskid;

	//! 貸し出すメモリブロックからリンクヘッダを削除する.
	return (BYTE *)((DWORD)blk + sizeof(WIHDR));
}

/****************************************************************************/
/*!
 *	@brief	メモリブロックを返却して空きブロックにする.
 *
 *	@param	[in]	mpf		固定長メモリプール･オブジェクトのポインタ.
 *	@param	[in]	blk		返却するメモリブロックのポインタ.
 *
 *	@retval	なし.
 */
static void		ReleaseFreeMem( WIMPFOBJ *mpf, WIHDR* blk )
{
	WIHDR *ptr;

	//! 未使用メモリブロックキューに返却されたメモリブロックを追加する.
	if( !mpf->FreeQue ){
		mpf->FreeQue = blk;
	}else{
		for( ptr = mpf->FreeQue; ptr->Next; ptr = ptr->Next ) ;
		ptr->Next = blk;
	}
	//! 貸し出し中のメモリブロックキューから返却されたメモリブロックを削除する.
	if( mpf->UsedQue == blk ){
		mpf->UsedQue  = blk->Next;
	}else{
		ptr = mpf->UsedQue;
		while( ptr ){
			if( ptr->Next == blk ){
				ptr->Next = blk->Next;
				break;
			}
			ptr = ptr->Next;
		}
	}
	//! 返却されたメモリブロックのリンクポインタをクリアする.
	blk->Next = NULL;
	blk->Id   = 0;
}

/****************************************************************************/
/*!
 *	@brief	メモリブロック獲得待ちをしているタスクにメモリを貸し出す.
 *
 *	@param	[in]	mpf		固定長メモリプール･オブジェクトのポインタ.
 *
 *	@retval	なし.
 */
static void		MemAllocWaitTask( WIMPFOBJ *mpf )
{
	WITSKOBJ *tsk;

	tsk = (WITSKOBJ *)mpf->WaitQue;
	while( tsk ){
		//! 空いているメモリブロックを取得する.
		tsk->Param[0] = GetFreeMem( mpf, tsk->Hdr.Id );
		if( !tsk->Param[0] ){
			break;
		}
		//! スリープしているタスクを起床させる.
		wi_TaskWakeup( tsk->Hdr.Id, TTW_MPF, NULL );

		//! 待ち行列から次のタスクを取り出す.
		tsk = tsk->QueLink;
	}
}

/* End of file */
