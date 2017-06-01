/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_mutex.c
 *
 *	@brief	Windows版 iTRONサービスコール (ミューテックス).
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_mutex.h"

/****************************************************************************
 *
 * ローカル変数定義.
 *
 ****************************************************************************/
static WIHDR	*ObjList;			//!< ミューテックス･リストのポインタ.

/****************************************************************************/
/*!
 *	@brief	ミューテックスの初期処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_InitMutex( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	ミューテックスの終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_QuitMutex( void )
{
	WIHDR		*next_ptr;
	WIMTXOBJ	*p = (WIMTXOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! ミューテックス･オブジェクト構造体を解放する.
		SAFE_RELEASE( p );

		//! 次のミューテックス･オブジェクト構造体を取り出す.
		p = (WIMTXOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	ミューテックスの生成.
 *
 *	@param	[in]	id		ミューテックスID番号.
 *	@param	[in]	obj		ミューテックス･オブジェクト構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_CreateMutex( INT id, const WIMTXOBJ *obj )
{
	ER			ercd;
	WIMTXOBJ	*p;

	//! ミューテックス･オブジェクトを作成する.
	p = (WIMTXOBJ *)wi_CreateObject( id, TMAX_MAXMTX, sizeof(WIMTXOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストにミューテックスを追加する.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	ミューテックスの削除.
 *
 *	@param	[in]	id		ミューテックスID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_DeleteMutex( INT id )
{
	ER			ercd;
	WIMTXOBJ	*p;

	//! ミューテックスIDのオブジェクトを取得する.
	p = (WIMTXOBJ *)wi_FindObject( id, TMAX_MAXMTX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストから該当するミューテックスを取り除く.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! 待ちタスクキューを解放する.
	wi_WakeupDelResource( p->WaitQue );

	//! ミューテックス･オブジェクト構造体を解放する.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	ミューテックスをロックする.
 *
 *	@param	[in]	id		ミューテックスID番号.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		wi_LockMutex( INT id, TMO tmout )
{
	INT			tsk_id;
	ER			ercd;
	WIMTXOBJ	*p;

	//! ミューテックスIDのオブジェクトを取得する.
	p = (WIMTXOBJ *)wi_FindObject( id, TMAX_MAXMTX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 非コンテキストのタスクから呼び出された場合はエラーにする.
	tsk_id = wi_GetActiveTaskId();
	if( tsk_id == 0 ){
		return E_CTX;
	}
	//! 多重ロックはエラーにする.
	if( p->LockId == tsk_id ){
		return E_ILUSE;
	}
	//! ミューテックスがロックされていなければ、ロックして終了する.
	if( p->LockId == 0 ){
		p->LockId  = tsk_id;
		return E_OK;
	}
	//! ロックが解除されるまでタスクをスリープさせる.
	ercd = wi_TaskWait( id, TTW_MTX, tmout, p->Attribute, &(p->WaitQue) );
	if( ercd == E_OK ){
		p->LockId = tsk_id;
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ミューテックスのロックを解除する.
 *
 *	@param	[in]	id		ミューテックスID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_UnlockMutex( INT id )
{
	ER			ercd;
	WIMTXOBJ	*p;

	//! ミューテックスIDのオブジェクトを取得する.
	p = (WIMTXOBJ *)wi_FindObject( id, TMAX_MAXMTX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ミューテックスをロックしているタスクと違う場合はエラーにする.
	if( p->LockId != wi_GetActiveTaskId() ){
		return E_ILUSE;
	}
	p->LockId = 0;

	//! ロック解除待ちをしているタスクがある場合はタスクを起床させる.
	if( p->WaitQue ){
		wi_TaskWakeup( p->WaitQue->Id, TTW_MTX, &(p->WaitQue) );
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	ミューテックスの状態参照.
 *
 *	@param	[in]	id		ミューテックスID番号.
 *	@param	[in]	sts		ミューテックス状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_RefarenceMutex( INT id, WIMTXSTAT *sts )
{
	ER			ercd;
	WIMTXOBJ	*p;

	//! ミューテックスIDのオブジェクトを取得する.
	p = (WIMTXOBJ *)wi_FindObject( id, TMAX_MAXMTX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ミューテックスの状態を構造体にセットする.
	sts->LockId = p->LockId;
	sts->WaitId = wi_GetWaitTaskListFirstId( p->WaitQue );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	削除されるタスクを待ち行列から削除する.
 *
 *	@param	[in]	id		削除されるタスクID番号.
 *
 *	@retval	なし.
 */
void	wi_AllReleaseMutex( INT id )
{
	WIMTXOBJ *p;

	for( p = (WIMTXOBJ *)ObjList; p; p = (WIMTXOBJ *)p->Hdr.Next ){

		//! 削除されるタスクを待ち行列から削除する.
		p->WaitQue = wi_DelWaitTaskList( id, p->WaitQue );
	}
}

/* End of file */
