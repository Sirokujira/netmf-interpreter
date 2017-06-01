/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_semaphore.c
 *
 *	@brief	Windows版 iTRONサービスコール (セマフォ).
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include <process.h>
#include "wi_semaphore.h"

/****************************************************************************
 *
 * ローカル変数定義.
 *
 ****************************************************************************/
static WIHDR	*ObjList;			//!< セマフォ･リストのポインタ.

/****************************************************************************/
/*!
 *	@brief	セマフォ管理の初期処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_InitSemaphore( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	セマフォ管理の終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_QuitSemaphore( void )
{
	WIHDR		*next_ptr;
	WISEMOBJ	*p = (WISEMOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! セマフォ構造体を解放する.
		SAFE_RELEASE( p );

		//! 次のセマフォ構造体を取り出す.
		p = (WISEMOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	セマフォの生成.
 *
 *	@param	[in]	id		セマフォID番号.
 *	@param	[in]	obj		セマフォ構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_CreateSemaphore( INT id, const WISEMOBJ *obj )
{
	ER			ercd;
	WISEMOBJ	*p;

	//! 引数が不正な場合はエラーにする.
	if( obj->SemCnt > obj->MaxCnt || obj->MaxCnt == 0 ){
		return E_PAR;
	}
	//! セマフォ･オブジェクトを作成する.
	p = (WISEMOBJ *)wi_CreateObject( id, TMAX_MAXSEM, sizeof(WISEMOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストにセマフォを追加する.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	セマフォの削除.
 *
 *	@param	[in]	id		セマフォID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_DeleteSemaphore( INT id )
{
	ER			ercd;
	WISEMOBJ	*p;

	//! セマフォIDのオブジェクトを取得する.
	p = (WISEMOBJ *)wi_FindObject( id, TMAX_MAXSEM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストから該当するセマフォを取り除く.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! 待ちタスクキューを解放する.
	wi_WakeupDelResource( p->WaitQue );

	//! セマフォ･オブジェクト構造体を解放する.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	セマフォ資源の返却.
 *
 *	@param	[in]	id		セマフォID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_SignalSemaphore( INT id )
{
	ER			ercd;
	WISEMOBJ	*p;

	//! セマフォIDのオブジェクトを取得する.
	p = (WISEMOBJ *)wi_FindObject( id, TMAX_MAXSEM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! セマフォカウントを+1する.
	if( p->SemCnt < p->MaxCnt ){
		p->SemCnt++;
	}
	//! セマフォの獲得待ちをしているタスクがある場合はタスクを起床させる.
	if( p->WaitQue ){
		wi_TaskWakeup( p->WaitQue->Id, TTW_SEM, &(p->WaitQue) );
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	セマフォ資源の獲得.
 *
 *	@param	[in]	id		セマフォID番号.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		wi_WaitSemaphore( INT id, TMO tmout )
{
	ER			ercd;
	WISEMOBJ	*p;

	//! セマフォIDのオブジェクトを取得する.
	p = (WISEMOBJ *)wi_FindObject( id, TMAX_MAXSEM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! セマフォ･カウンタが0でなければ、セマフォ資源を獲得させて終了する.
	if( p->SemCnt > 0 ){
		p->SemCnt--;
		return E_OK;
	}
	//! セマフォ資源が返却されるまでタスクをスリープさせる.
	ercd = wi_TaskWait( id, TTW_SEM, tmout, p->Attribute, &(p->WaitQue) );
	if( ercd == E_OK ){
		if( p->SemCnt > 0 ){
			p->SemCnt--;
		}
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	セマフォ状態の参照.
 *
 *	@param	[in]	id		セマフォID番号.
 *	@param	[in]	sts		セマフォ状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_RefarenceSemaphore( INT id, WISEMSTAT *sts )
{
	ER			ercd;
	WISEMOBJ	*p;

	//! セマフォIDのオブジェクトを取得する.
	p = (WISEMOBJ *)wi_FindObject( id, TMAX_MAXSEM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! セマフォの状態を構造体にセットする.
	sts->WaitId  = wi_GetWaitTaskListFirstId( p->WaitQue );
	sts->SemCnt  = p->SemCnt;
	sts->ExtInfo = p->ExtInfo;
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
void	wi_AllReleaseSemaphore( INT id )
{
	WISEMOBJ *p;

	for( p = (WISEMOBJ *)ObjList; p; p = (WISEMOBJ *)p->Hdr.Next ){

		//! 削除されるタスクを待ち行列から削除する.
		p->WaitQue = wi_DelWaitTaskList( id, p->WaitQue );
	}
}

/* End of file */
