/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_variable_mempool.c
 *
 *	@brief	Windows版 iTRONサービスコール (可変長メモリプール).
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_variable_mempool.h"

/****************************************************************************
 *
 * 構造体定義.
 *
 ****************************************************************************/
/*!
 *
 * @brief 可変長メモリブロックのヘッダ情報構造体.
 *
 */
typedef struct {
	INT		Size;		//!< メモリブロックのサイズ (最上位ビット=1のとき貸し出し中).
	DWORD	TaskId;		//!< メモリブロックを貸し出したタスクのID.
} MEMHDR;

/****************************************************************************
 *
 * ローカル関数定義.
 *
 ****************************************************************************/
static BYTE		*AllocVerMem( INT len, BYTE* buf, INT max_size, DWORD tskid );
static BOOL		FreeVarMem( BYTE* adr, BYTE* buf, INT max_size );
static INT		GetFreeBufSize( INT *max_free, BYTE* buf, INT max_size );
static void		MemAllocWaitTask( WIMPLOBJ *mpl );

/****************************************************************************
 *
 * ローカル変数定義.
 *
 ****************************************************************************/
static WIHDR		*ObjList;		//!< 可変長メモリプール･リストのポインタ.

/****************************************************************************/
/*!
 *	@brief	可変長メモリプールの初期処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_InitVarMemPool( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリプールの終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_QuitVarMemPool( void )
{
	WIHDR		*next_ptr;
	WIMPLOBJ	*p = (WIMPLOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! メモリバッファを解放する.
		SAFE_RELEASE( p->MemBuf );

		//! 可変長メモリプール･オブジェクト構造体を解放する.
		SAFE_RELEASE( p );

		//! 次のメモリプール･オブジェクト構造体を取り出す.
		p = (WIMPLOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリプールの生成.
 *
 *	@param	[in]	id		メモリプールID番号.
 *	@param	[in]	obj		可変長メモリプール構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_CreateVarMemPool( INT id, const WIMPLOBJ *obj )
{
	ER			ercd;
	MEMHDR		*hdr;
	WIMPLOBJ	*p;

	//! 引数が不正な場合はエラーにする.
	if( obj->MemSize <= 0 ){
		return E_PAR;
	}
	//! 可変長メモリプール･オブジェクトを作成する.
	p = (WIMPLOBJ *)wi_CreateObject( id, TMAX_MAXMPL, sizeof(WIMPLOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! メモリプールのバッファを確保する.
	p->MemBuf = (BYTE*)malloc( obj->MemSize );
	if( !p->MemBuf ){
		SAFE_RELEASE( p );
		return E_NOMEM;
	}
	//! 確保したバッファをクリアする.
	memset( p->MemBuf, 0, obj->MemSize );

	//! バッファの先頭にメモリブロックヘッダを付加する.
	hdr         = (MEMHDR *)p->MemBuf;
	hdr->Size   = obj->MemSize;
	hdr->TaskId = 0;

	//! リストに可変長メモリプールを追加する.
	wi_AddObject( (WIHDR *)p, &ObjList );

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリプールの削除.
 *
 *	@param	[in]	id		メモリプールID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_DeleteVarMemPool( INT id )
{
	ER			ercd;
	WIMPLOBJ	*p;

	//! メモリプールIDのオブジェクトを取得する.
	p = (WIMPLOBJ *)wi_FindObject( id, TMAX_MAXMPL, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストから該当するメモリプールを取り除く.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! 待ちタスクキューを解放する.
	wi_WakeupDelResource( p->WaitQue );

	//! メモリプールのバッファを解放する.
	SAFE_RELEASE( p->MemBuf );

	//! 可変長メモリプール･オブジェクト構造体を解放する.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリ･ブロックの獲得.
 *
 *	@param	[in]	id		メモリプールID番号.
 *	@param	[in]	adr		メモリブロックのアドレスを格納する領域のポインタ.
 *	@param	[in]	size	メモリブロックのサイズ.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		wi_GetVarMemPool( INT id, VP adr, INT size, TMO tmout )
{
	ER			ercd;
	WITSKOBJ	*tsk;
	WIMPLOBJ	*p;
	BYTE		*blk;

	//! メモリプールIDのオブジェクトを取得する.
	p = (WIMPLOBJ *)wi_FindObject( id, TMAX_MAXMPL, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 引数が不正な場合はエラーにする.
	if( !adr || size <= 0 || size > (INT)(p->MemSize - sizeof(MEMHDR)) ){
		return E_PAR;
	}
	*((BYTE **)adr) = NULL;

	//! タスク以外からの呼び出しの場合はエラーにする.
	tsk = wi_GetTaskObject( TSK_SELF );
	if( !tsk ){
		return E_CTX;
	}
	//! 指定されたサイズの空きメモリを確保する.
	blk = AllocVerMem( size, p->MemBuf, p->MemSize, tsk->Hdr.Id );

	//! メモリが確保できない場合.
	if( !blk ){
		//! 必要なメモリサイズをタスク･オブジェクトにセットする.
		tsk->Param[0] = (VP)size;
		tsk->Param[1] = NULL;

		//! メモリブロックが返却されるまでタスクをスリープさせる.
		ercd = wi_TaskWait( id, TTW_MPL, tmout, p->Attribute, &(p->WaitQue) );

		//! エラー検出と同時にメモリの確保が出来てしまった場合、メモリは返却する.
		if( ercd != E_OK ){
			if( tsk->Param[1] ){
				FreeVarMem( tsk->Param[1], p->MemBuf, p->MemSize );
			}
			return ercd;
		}
		//! メモリブロックの返却処理で確保したメモリブロックのアドレスを取り出す.
		blk = (BYTE *)(tsk->Param[1]);
	}
	//! 貸し出すメモリのアドレスを戻り値に格納する.
	*((BYTE **)adr) = blk;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリ･ブロックの返却.
 *
 *	@param	[in]	id		メモリプールID番号.
 *	@param	[in]	adr		返却するメモリ･ブロックのアドレス.
 *
 *	@retval	エラーコード.
 */
ER		wi_ReleaseVarMemPool( INT id, VP adr )
{
	ER			ercd;
	WIMPLOBJ	*p;

	//! メモリプールIDのオブジェクトを取得する.
	p = (WIMPLOBJ *)wi_FindObject( id, TMAX_MAXMPL, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 引数が不正な場合はエラーにする.
	if( !adr ){
		return E_PAR;
	}
	//! 返却されたメモリブロックを解放する.
	if( !FreeVarMem( (BYTE*)adr, p->MemBuf, p->MemSize ) ){
		return E_PAR;
	}
	//! メモリブロック獲得待ちのタスクがある場合、メモリを確保する.
	MemAllocWaitTask( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリプールの参照.
 *
 *	@param	[in]	id		メモリプールID番号.
 *	@param	[out]	sts		メモリプール状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_RefarenceVarMemPool( INT id, WIMPLSTAT *sts )
{
	ER			ercd;
	WIMPLOBJ	*p;
	INT			total_free,max_free;

	//! メモリプールIDのオブジェクトを取得する.
	p = (WIMPLOBJ *)wi_FindObject( id, TMAX_MAXMPL, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 空きメモリのサイズを取得する.
	total_free = GetFreeBufSize( &max_free, p->MemBuf, p->MemSize );

	//! 可変長メモリプールの状態を構造体にセットする.
	sts->WaitId        = wi_GetWaitTaskListFirstId( p->WaitQue );
	sts->TotalFreeSize = total_free;
	sts->MaxFreeSize   = max_free;
	sts->ExtInfo       = p->ExtInfo;
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
void	wi_AllReleaseVarMemPool( INT id )
{
	WIMPLOBJ *p = (WIMPLOBJ *)ObjList;

	while( p ){
		INT		i,j;
		MEMHDR	*hdr1,*hdr2;

		//! 削除されるタスクに貸し出していたメモリブロックを全て解放する.
		for( i = 0; i < p->MemSize; ){

			//! バッファからメモリブロックのヘッダを取り出す.
			hdr1 = (MEMHDR *)(&p->MemBuf[i]);

			//! メモリブロックを空きブロックにする.
			if( hdr1->TaskId == id ){
				hdr1->TaskId = 0;
			}
			//! 次のメモリブロックを取り出す.
			i += hdr1->Size;
		}
		//! 隣接した空きメモリブロックを結合する.
		for( i = 0; i < p->MemSize; ){

			//! バッファからメモリブロックのヘッダを取り出す.
			hdr1 = (MEMHDR *)(&p->MemBuf[i]);

			/*!
			 * 空きブロックの場合、次のブロックも空きブロックのときは
			 * メモリブロックを結合して1つにする.
			 */
			if( hdr1->TaskId == 0 ){
				j = i + hdr1->Size;
				if( j < (p->MemSize - (signed)sizeof(MEMHDR)) ){
					hdr2 = (MEMHDR *)(&p->MemBuf[j]);
					if( hdr2->TaskId == 0 ){
						hdr1->Size += hdr2->Size;
						continue;
					}
				}
			}
			//! メモリブロックを結合しなかったときは次のメモリブロックを取り出す.
			i += hdr1->Size;
		}
		//! 待ち行列から消滅するタスクを削除する.
		p->WaitQue = wi_DelWaitTaskList( id, p->WaitQue );

		//! メモリブロック獲得待ちのタスクがある場合は、空きメモリの確保に再挑戦する.
		MemAllocWaitTask( p );

		//! 次のメモリプール構造体をを取り出す.
		p = (WIMPLOBJ *)(p->Hdr.Next);
	}
}

/****************************************************************************/
/*!
 *	@brief	指定したサイズのメモリブロックを取得する.
 *
 *	@param	[in]	len			取得するメモリブロックのサイズ.
 *	@param	[in]	buf			メモリバッファのポインタ.
 *	@param	[in]	max_size	メモリバッファのサイズ.
 *	@param	[in]	tskid		メモリを取得するタスクのID.
 *
 *	@retval	取得したメモリブロックのポインタ.
 */
static BYTE	*AllocVerMem( INT len, BYTE* buf, INT max_size, DWORD tskid )
{
	MEMHDR	*hdr;
	INT		i,req_size,remain;

	//! 取得するサイズにヘッダサイズを加えて必要なメモリサイズを計算する.
	req_size = len + sizeof(MEMHDR);

	for( i = 0; i < max_size; ){

		//! バッファからメモリブロックのヘッダを取り出す.
		hdr = (MEMHDR *)(&buf[i]);

		if( hdr->TaskId == 0 ){
			if( hdr->Size >= req_size ){
				//! 空きブロックのサイズから必要なサイズを引いた余りを計算しておく.
				remain = hdr->Size - req_size;

				//! 空きブロックを「貸し出し中」にする.
				hdr->Size   = req_size;
				hdr->TaskId = tskid;

				if( remain > sizeof(MEMHDR) ){
					//! 空きブロックに余りがある場合はメモリブロックを分割して余りの空きブロックを作成する.
					hdr         = (MEMHDR *)(&buf[i+req_size]);
					hdr->Size   = remain;
					hdr->TaskId = 0;
				}else{
					//! 余りがヘッダサイズ以下の場合、貸し出したメモリサイズに余りも加えておく.
					hdr->Size += remain;
				}
				//! 戻り値は使用可能は空きブロックの先頭アドレスを返す.
				return &buf[i + sizeof(MEMHDR)];
			}
		}
		//! 次のメモリブロックを取り出す.
		i += hdr->Size;
	}
	return NULL;
}

/****************************************************************************/
/*!
 *	@brief	メモリブロックを返却して空きブロックにする.
 *
 *	@param	[in]	adr			返却するメモリブロックのポインタ.
 *	@param	[in]	buf			メモリバッファのポインタ.
 *	@param	[in]	max_size	メモリバッファのサイズ.
 *
 *	@retval	TRUE = OK. / FALSE = NG.
 */
static BOOL		FreeVarMem( BYTE* adr, BYTE* buf, INT max_size )
{
	MEMHDR	*hdr1,*hdr2,*hdr3;
	INT		i,j,pos;

	//! 返却するメモリブロックのメモリバッファ上の位置を計算する.
	pos = ((INT)adr - (INT)buf) - (INT)sizeof(MEMHDR);

	//! 返却するメモリブロックがメモリバッファの範囲外の場合はエラーにする.
	if( pos < 0 || pos >= (max_size - (INT)sizeof(MEMHDR)) ){
		return FALSE;
	}
	//! メモリブロックの先頭からリンクを辿って、返却するメモリブロックを探す.
	hdr1 = NULL;
	for( i = 0; i < max_size && i <= pos; ){

		//! バッファからメモリブロックのヘッダを取り出す.
		hdr2 = (MEMHDR *)(&buf[i]);

		//! メモリブロックのバイト数が 0 の場合、メモリバッファが壊されているので処理を中断する.
		if( hdr2->Size == 0 ){
			break;
		}
		if( i == pos ){
			//! 返却するブロックが空きブロックの場合はエラーにする.
			if( hdr2->TaskId == 0 ){
				break;
			}
			//! メモリブロックを空きブロックにする.
			hdr2->TaskId = 0;

			/*!
			 * 次のブロックが空きブロックの場合、返却したブロックと結合して
			 * 次のブロックを消滅させる.
			 */
			j = i + hdr2->Size;
			if( j < (max_size - (INT)sizeof(MEMHDR)) ){
				hdr3 = (MEMHDR *)(&buf[j]);
				if( hdr3->TaskId == 0 ){
					hdr2->Size += hdr3->Size;
				}
			}
			/*!
			 * 1つ手前のブロックが空きブロックの場合、返却したブロックと結合して
			 * 返却したブロックを消滅させる.
			 */
			if( hdr1 && hdr1->TaskId == 0 ){
				hdr1->Size += hdr2->Size;
			}
			return TRUE;
		}
		//! 次のメモリブロックを取り出す.
		i += hdr2->Size;

		//! 1つ手前のメモリブロックのヘッダ位置を更新する.
		hdr1 = hdr2;
	}
	return FALSE;
}

/****************************************************************************/
/*!
 *	@brief	空きバッファのサイズを取得する.
 *
 *	@param	[out]	max_free	最大の連続空き領域のサイズを格納する領域のポインタ.
 *	@param	[in]	buf			メモリバッファのポインタ.
 *	@param	[in]	max_size	メモリバッファのサイズ.
 *
 *	@retval	空き領域の合計サイズ.
 */
static INT	GetFreeBufSize( INT *max_free, BYTE* buf, INT max_size )
{
	MEMHDR	*hdr;
	INT		i,total_free;

	*max_free  = 0;
	total_free = 0;

	for( i = 0; i < max_size; ){

		//! バッファからメモリブロックのヘッダを取り出す.
		hdr = (MEMHDR *)(&buf[i]);

		//! 空きメモリブロックの場合.
		if( hdr->TaskId == 0 ){
			//! より大きな空きメモリブロックを見つけた場合、サイズを保存する.
			if( *max_free < hdr->Size ){
				*max_free = hdr->Size;
			}
			/*!
			 * 空きメモリの合計サイズに空きブロックのサイズを加算する.
			 * (メモリブロックのヘッダサイズは空きサイズに含めない)
			 */
			total_free += (hdr->Size - sizeof(MEMHDR));
		}
		//! 次のメモリブロックを取り出す.
		i += hdr->Size;
	}
	//! 最大の連続した空き領域のサイズからメモリブロックのヘッダサイズを引く.
	if( *max_free != 0 ){
		*max_free -= sizeof(MEMHDR);
	}
	return total_free;
}

/****************************************************************************/
/*!
 *	@brief	メモリブロック獲得待ちをしているタスクにメモリを貸し出す.
 *
 *	@param	[in]	mpl			可変長メモリプール･オブジェクトのポインタ.
 *
 *	@retval	なし.
 */
static void		MemAllocWaitTask( WIMPLOBJ *mpl )
{
	WITSKOBJ *tsk;

	tsk = (WITSKOBJ *)mpl->WaitQue;
	while( tsk ){
		//! 指定されたサイズの空きメモリを確保する.
		tsk->Param[1] = AllocVerMem( (INT)(tsk->Param[0]), mpl->MemBuf, mpl->MemSize, tsk->Hdr.Id );
		if( !tsk->Param[1] ){
			break;
		}
		//! スリープしているタスクを起床させる.
		wi_TaskWakeup( tsk->Hdr.Id, TTW_MPL, NULL );

		//! 待ち行列から次のタスクを取り出す.
		tsk = tsk->QueLink;
	}
}

/* End of file */
