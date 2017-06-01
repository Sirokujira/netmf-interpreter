/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_rendezvous_port.cpp
 *
 *	@brief	Windows版 iTRONサービスコール (ランデブ).
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_rendezvous_port.h"

/****************************************************************************
 *
 * ローカル関数定義.
 *
 ****************************************************************************/
static WITSKOBJ	*SatisfyRendezvous( WITSKOBJ *tsk, UINT ptn );
static ER		CreateRdv( INT tskid, INT rsize );
static void		DeleteRdv( INT no );

/****************************************************************************
 *
 * ローカル変数定義.
 *
 ****************************************************************************/
static INT			RdvSeqNo;		//!< ランデブ番号の生成用カウンタ.
static WIHDR		*PortList;		//!< ランデブポート･リストのポインタ.
static WIHDR		*RdvList;		//!< ランデブ･リストのポインタ.

/****************************************************************************/
/*!
 *	@brief	ランデブの初期処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_InitRendPort( void )
{
	RdvSeqNo = 0;
	PortList = NULL;
	RdvList  = NULL;
}

/****************************************************************************/
/*!
 *	@brief	ランデブの終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_QuitRendPort( void )
{
	WIHDR		*next_ptr;
	WIPOROBJ	*port;
	WIRDVOBJ	*rdv;

	//! ランデブポート･オブジェクトを解放する.
	port = (WIPOROBJ *)PortList;
	while( port ){
		next_ptr = port->Hdr.Next;

		//! ランデブポート･オブジェクト構造体を解放する.
		SAFE_RELEASE( port );

		//! 次のランデブポート･オブジェクト構造体を取り出す.
		port = (WIPOROBJ *)next_ptr;
	}

	//! 成立したランデブ･オブジェクトを解放する.
	rdv = (WIRDVOBJ *)RdvList;
	while( rdv ){
		next_ptr = rdv->Hdr.Next;

		//! ランデブ･オブジェクト構造体を解放する.
		SAFE_RELEASE( rdv );

		//! 次のランデブ･オブジェクト構造体を取り出す.
		rdv = (WIRDVOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	ランデブポートの生成.
 *
 *	@param	[in]	id		ランデブ･ポートID番号.
 *	@param	[in]	obj		ランデブ･オブジェクト構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_CreateRendPort( INT id, const WIPOROBJ *obj )
{
	ER			ercd;
	WIPOROBJ	*p;

	//! 不正な引数の場合はエラーにする.
	if( obj->MaxCalMsg == 0 || obj->MaxRepMsg == 0 ){
		return E_PAR;
	}
	//! ランデブポート･オブジェクトを作成する.
	p = (WIPOROBJ *)wi_CreateObject( id, TMAX_MAXPOR, sizeof(WIPOROBJ), obj, PortList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストにランデブポートを追加する.
	wi_AddObject( (WIHDR *)p, &PortList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	ランデブポートの削除.
 *
 *	@param	[in]	id		ランデブポートID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_DeleteRendPort( INT id )
{
	ER			ercd;
	WIPOROBJ	*p;

	//! ランデブポートIDのオブジェクトを取得する.
	p = (WIPOROBJ *)wi_FindObject( id, TMAX_MAXPOR, PortList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストから該当するランデブポートを取り除く.
	wi_DelObject( (WIHDR *)p, &PortList );

	//! 待ちタスクキューを解放する.
	wi_WakeupDelResource( p->CalWaitQue );
	wi_WakeupDelResource( p->AcpWaitQue );

	//! ランデブポート･オブジェクト構造体を解放する.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	ランデブ呼び出し.
 *
 *	@param	[in]	id			ランデブポートID番号.
 *	@param	[in]	ptn			呼び出し側選択条件のビットパターン.
 *	@param	[in]	msg			メッセージのアドレス.
 *	@param	[in]	csize		呼び出しメッセージのサイズ.
 *	@param	[out]	rsize		応答メッセージのサイズを格納する領域のポインタ.
 *	@param	[in]	tmout		タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		wi_CallRendPort( INT id, UINT ptn, VP msg, INT csize, INT *rsize, TMO tmout )
{
	ER			ercd;
	WIPOROBJ	*p;
	WITSKOBJ	*acp_tsk,*cal_tsk;

	//! ランデブポートIDのオブジェクトを取得する.
	p = (WIPOROBJ *)wi_FindObject( id, TMAX_MAXPOR, PortList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 引数が不正な場合はエラーにする.
	if( !rsize || p->MaxCalMsg < csize ){
		return E_PAR;
	}
	//! 自タスクのタスクコンテキストを取り出す.
	cal_tsk = wi_GetTaskObject( TSK_SELF );
	if( !cal_tsk ){
		return E_CTX;
	}
	cal_tsk->Param[0] = (VP)ptn;
	cal_tsk->Param[1] = (VP)msg;
	cal_tsk->Param[2] = (VP)csize;

	//! ランデブ受付待ちをしているタスクに対してランデブが成立するかどうかを調べる.
	acp_tsk = SatisfyRendezvous( (WITSKOBJ *)(p->AcpWaitQue), ptn );

	if( !acp_tsk ){
		//! ランデブが成立するまでタスクをスリープさせる.
		ercd = wi_TaskWait( id, TTW_CAL, tmout, p->Attribute, &(p->CalWaitQue) );
		if( ercd == E_OK ){
			*rsize = (INT)cal_tsk->Param[2];
		}
	}else{
		//! 成立したランデブを登録する.
		ercd = CreateRdv( cal_tsk->Hdr.Id, p->MaxRepMsg );
		if( ercd != E_OK ){
			return ercd;
		}
		//! 成立したランデブ番号を受付タスクに通知する.
		acp_tsk->Param[3] = (VP)RdvSeqNo;

		//! ランデブ受付タスクにランデブ呼び出しメッセージをコピーする.
		if( acp_tsk->Param[1] && msg && csize > 0 ){
			memcpy( acp_tsk->Param[1], msg, csize );
			acp_tsk->Param[2] = (VP)csize;
		}else{
			acp_tsk->Param[2] = 0;
		}
		wi_TaskWakeup( acp_tsk->Hdr.Id, TTW_ACP, &(p->AcpWaitQue) );

		//! ランデブが終了するまでタスクをスリープさせる.
		ercd = wi_TaskWait( RdvSeqNo, TTW_RDV, tmout, 0, NULL );
		if( ercd == E_OK ){
			*rsize = (INT)cal_tsk->Param[2];
		}
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ランデブ受け付け.
 *
 *	@param	[in]	id			ランデブポートID番号.
 *	@param	[in]	ptn			受け付け側選択条件のビットパターン.
 *	@param	[out]	no			ランデブ番号を格納する領域のポインタ.
 *	@param	[out]	msg			呼び出しメッセージを格納する領域のポインタ.
 *	@param	[out]	size		呼び出しメッセージのサイズを格納する領域のポインタ.
 *	@param	[in]	tmout		タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		wi_AcceptRendPort( INT id, UINT ptn, INT *no, VP msg, INT *size, TMO tmout )
{
	ER			ercd;
	WIPOROBJ	*p;
	WITSKOBJ	*cal_tsk,*acp_tsk;

	//! 引数が不正な場合はエラーにする.
	if( !no || !size ){
		return E_PAR;
	}
	//! ランデブポートIDのオブジェクトを取得する.
	p = (WIPOROBJ *)wi_FindObject( id, TMAX_MAXPOR, PortList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 自タスクのタスクコンテキストを取り出す.
	acp_tsk = wi_GetTaskObject( TSK_SELF );
	if( !acp_tsk ){
		return E_CTX;
	}
	acp_tsk->Param[0] = (VP)ptn;
	acp_tsk->Param[1] = (VP)msg;
	acp_tsk->Param[2] = (VP)0;

	//! ランデブ呼び出しをしているタスクに対してランデブが成立するかどうかを調べる.
	cal_tsk = SatisfyRendezvous( (WITSKOBJ *)(p->CalWaitQue), ptn );

	if( !cal_tsk ){
		//! ランデブが成立するまでタスクをスリープさせる.
		ercd = wi_TaskWait( id, TTW_ACP, tmout, p->Attribute, &(p->AcpWaitQue) );
		if( ercd != E_OK ){
			return ercd;
		}
		*size = (INT)acp_tsk->Param[2];
		*no   = (INT)acp_tsk->Param[3];
	}else{
		//! 成立したランデブを登録する.
		ercd = CreateRdv( cal_tsk->Hdr.Id, p->MaxRepMsg );
		if( ercd != E_OK ){
			return ercd;
		}
		//! ランデブ番号を戻り値にセットする.
		*no = RdvSeqNo;

		//! 呼び出しメッセージを呼び出し側タスクからコピーする.
		if( cal_tsk->Param[1] && (INT)cal_tsk->Param[2] > 0 ){
			memcpy( msg, cal_tsk->Param[1], (INT)cal_tsk->Param[2] );
			*size = (INT)cal_tsk->Param[2];
		}else{
			*size = 0;
		}
		//! 呼び出し側タスクを待ち行列から削除する.
		p->CalWaitQue = wi_DelWaitTaskList( cal_tsk->Hdr.Id, p->CalWaitQue );

		//! 呼び出し側タスクのイベント待ち状態を「ランデブ終了待ち」にする.
		cal_tsk->EventType = TTW_RDV;
		cal_tsk->WaitId    = RdvSeqNo;
		cal_tsk->QueLink   = NULL;

		ercd = E_OK;
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ランデブの回送
 *
 *	@param	[in]	id		ランデブポートID番号.
 *	@param	[in]	ptn		受け付け側選択条件のビットパターン.
 *	@param	[in]	no		ランデブ番号.
 *	@param	[in]	msg		呼び出しメッセージのポインタ.
 *	@param	[in]	size	呼び出しメッセージのサイズ.
 *
 *	@retval	エラーコード.
 */
ER		wi_FowardRendPort( INT id, UINT ptn, INT no, VP msg, INT size )
{
	ER			ercd;
	WIPOROBJ	*p;
	WITSKOBJ	*acp_tsk,*rdv_tsk;
	WIRDVOBJ	*rdv;

	//! ランデブポートIDのオブジェクトを取得する.
	p = (WIPOROBJ *)wi_FindObject( id, TMAX_MAXPOR, PortList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ランデブ番号のオブジェクトを取得する.
	rdv = (WIRDVOBJ *)wi_FindObject( no, TMAX_MAXRDV, RdvList, &ercd );
	if( !rdv ){
		return E_OBJ;
	}
	//! ランデブ終了待ちをしているタスクのコンテキストを取得する.
	rdv_tsk = wi_GetTaskObject( rdv->TaskId );
	if( !rdv_tsk ){
		return E_OBJ;
	}
	//! ランデブ受付待ちをしているタスクに対してランデブが成立するかどうかを調べる.
	acp_tsk = SatisfyRendezvous( (WITSKOBJ *)(p->AcpWaitQue), ptn );
	if( !acp_tsk ){

		//! ランデブ終了待ちタスクのイベント待ち状態を「ランデブ成立待ち」にする.
		rdv_tsk->EventType = TTW_CAL;
		rdv_tsk->WaitId    = p->Hdr.Id;

		//! ランデブ呼び出し待ち行列にランデブ終了待ちタスクを追加する.
		p->CalWaitQue = wi_AddWaitTaskList( rdv->TaskId, p->Attribute, p->CalWaitQue );
	}else{
		//! 成立したランデブを登録する.
		ercd = CreateRdv( rdv_tsk->Hdr.Id, p->MaxRepMsg );
		if( ercd != E_OK ){
			return ercd;
		}
		acp_tsk->Param[2] = 0;
		acp_tsk->Param[3] = (VP)RdvSeqNo;

		//! ランデブ受付タスクにランデブ回送メッセージをコピーする.
		if( acp_tsk->Param[1] && msg && size > 0 ){
			memcpy( acp_tsk->Param[1], msg, size );
			acp_tsk->Param[2] = (VP)size;
		}
		//! ランデブ受付待ちをしているタスクを起床する.
		wi_TaskWakeup( acp_tsk->Hdr.Id, TTW_ACP, &(p->AcpWaitQue) );
	}
	//! ランデブ･オブジェクトを削除する.
	DeleteRdv( no );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	ランデブの終了.
 *
 *	@param	[in]	rdvno		ランデブ番号.
 *	@param	[in]	msg			返答メッセージのポインタ.
 *	@param	[in]	size		返答メッセージのサイズ.
 *
 *	@retval	エラーコード.
 */
ER		wi_ReplayRendPort( INT no, VP msg, INT size )
{
	ER			ercd;
	WIRDVOBJ	*rdv;
	WITSKOBJ	*tsk;

	//! ランデブ番号のオブジェクトを取得する.
	rdv = (WIRDVOBJ *)wi_FindObject( no, TMAX_MAXRDV, RdvList, &ercd );
	if( !rdv ){
		return E_OBJ;
	}
	//! 引数が不正な場合はエラーにする.
	if( rdv->MaxRepMsg < size ){
		return E_PAR;
	}
	//! ランデブ終了待ちをしているタスクのコンテキストを取得する.
	tsk = wi_GetTaskObject( rdv->TaskId );
	if( !tsk ){
		ercd = E_OBJ;
	}else{
		//! 返答メッセージをランデブ終了待ちをしているタスクのメッセージ領域にコピーする.
		ercd = E_OK;
		if( tsk->Param[1] && msg ){
			if( (INT)tsk->Param[2] < size ){
				tsk->Param[2] = 0;
				ercd          = E_PAR;
			}else{
				memcpy( tsk->Param[1], msg, size );
				tsk->Param[2] = (VP)size;
			}
		}else{
			tsk->Param[2] = 0;
		}
		//! ランデブ終了待ちをしているタスクを起床する.
		wi_TaskWakeup( rdv->TaskId, TTW_RDV, NULL );
	}
	//! ランデブ･オブジェクトを削除する.
	DeleteRdv( no );
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ランデブポートの状態参照.
 *
 *	@param	[in]	id		ランデブポートID番号.
 *	@param	[out]	sts		ランデブポート状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_RefarenceRendPort( INT id, WIPORSTAT *sts )
{
	ER			ercd;
	WIPOROBJ	*p;

	//! ランデブポートIDのオブジェクトを取得する.
	p = (WIPOROBJ *)wi_FindObject( id, TMAX_MAXPOR, PortList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ランデブポートの状態を構造体にセットする.
	sts->CalWaitId = wi_GetWaitTaskListFirstId( p->CalWaitQue );
	sts->AcpWaitId = wi_GetWaitTaskListFirstId( p->AcpWaitQue );
	sts->ExtInfo   = p->ExtInfo;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	ランデブ状態の参照.
 *
 *	@param	[in]	no		ランデブ番号.
 *	@param	[out]	sts		ランデブ状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_RefarenceRendStat( INT no, WIRDVSTAT *sts )
{
	ER			ercd;
	WIRDVOBJ	*p;

	//! ランデブ番号のオブジェクトを取得する.
	p = (WIRDVOBJ *)wi_FindObject( no, TMAX_MAXRDV, RdvList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ランデブの状態を構造体にセットする.
	sts->WaitId = p->TaskId;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	ランデブが成立するかどうかを調べる.
 *
 *	@param	[in]	tsk		待ち行列の先頭のタスク･オブジェクトのポインタ..
 *	@param	[in]	ptn		選択条件のビットパターン.
 *
 *	@retval	ランデブが成立したタスク･オブジェクトのポインタ.
 */
static WITSKOBJ	*SatisfyRendezvous( WITSKOBJ *tsk, UINT ptn )
{
	while( tsk ){
		if( ((UINT)(tsk->Param[0]) & ptn) != 0 ){
			break;
		}
		tsk = tsk->QueLink;
	}
	return tsk;
}

/****************************************************************************/
/*!
 *	@brief	ランデブの生成.
 *
 *	@param	[in]	tskid	ランデブ終了待ちのタスクのID番号.
 *	@param	[in]	rsize	返答メッセージの最大サイズ.
 *
 *	@retval	エラーコード.
 */
static ER	CreateRdv( INT tskid, INT rsize )
{
	WIRDVOBJ *rdv;

	//! ランデブ番号をインクリメントする.
	if( RdvSeqNo >= TMAX_MAXRDV ){
		RdvSeqNo  = 1;
	}else{
		RdvSeqNo++;
	}
	//! ランデブ･オブジェクト構造体を確保する.
	rdv = (WIRDVOBJ *)malloc( sizeof(WIRDVOBJ) );
	if( !rdv ){
		return E_NOMEM;
	}
	memset( rdv, 0, sizeof(WIRDVOBJ) );
	rdv->Hdr.Id    = RdvSeqNo;
	rdv->TaskId    = tskid;
	rdv->MaxRepMsg = rsize;

	//! リストに成立したランデブを追加する.
	wi_AddObject( (WIHDR *)rdv, &RdvList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	ランデブの削除.
 *
 *	@param	[in]	no		ランデブ番号.
 *
 *	@retval	なし.
 */
static void	DeleteRdv( INT no )
{
	ER			ercd;
	WIRDVOBJ	*p;

	//! ランデブポートIDのオブジェクトを取得する.
	p = (WIRDVOBJ *)wi_FindObject( no, TMAX_MAXRDV, RdvList, &ercd );
	if( p ){
		//! リストから該当するランデブポートを取り除く.
		wi_DelObject( (WIHDR *)p, &RdvList );

		//! ランデブ･オブジェクト構造体を解放する.
		SAFE_RELEASE( p );
	}
}

/****************************************************************************/
/*!
 *	@brief	削除されるタスクを待ち行列から削除する.
 *
 *	@param	[in]	id		削除されるタスクID番号.
 *
 *	@retval	なし.
 */
void	wi_AllReleaseRendPort( INT id )
{
	WIPOROBJ *p;

	for( p = (WIPOROBJ *)PortList; p; p = (WIPOROBJ *)p->Hdr.Next ){

		//! 削除されるタスクを待ち行列から削除する.
		p->CalWaitQue = wi_DelWaitTaskList( id, p->CalWaitQue );
		p->AcpWaitQue = wi_DelWaitTaskList( id, p->AcpWaitQue );
	}
}

/* End of file */
