/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_event_flag.c
 *
 *	@brief	Windows版 iTRONサービスコール (イベントフラグ).
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_event_flag.h"

/****************************************************************************
 *
 * ローカル変数定義.
 *
 ****************************************************************************/
static WIHDR		*ObjList;		//!< イベントフラグ･リストのポインタ.

/****************************************************************************/
/*!
 *	@brief	イベントフラグ管理の初期処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_InitEvFlag( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグ管理の終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_QuitEvFlag( void )
{
	WIHDR		*next_ptr;
	WIFLGOBJ	*p = (WIFLGOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! イベントフラグ･オブジェクト構造体を解放する.
		SAFE_RELEASE( p );

		//! 次のイベントフラグ･オブジェクト構造体を取り出す.
		p = (WIFLGOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグの生成.
 *
 *	@param	[in]	id		イベントフラグID番号.
 *	@param	[in]	obj		イベントフラグ･オブジェクト構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_CreateEvFlag( INT id, WIFLGOBJ *obj )
{
	ER			ercd;
	WIFLGOBJ	*p;

	//! イベントフラグ･オブジェクトを作成する.
	p = (WIFLGOBJ *)wi_CreateObject( id, TMAX_MAXFLG, sizeof(WIFLGOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストにイベントフラグを追加する.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグの削除.
 *
 *	@param	[in]	id		イベントフラグID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_DeleteEvFlag( INT id )
{
	ER			ercd;
	WIFLGOBJ	*p;

	//! イベントフラグIDのオブジェクトを取得する.
	p = (WIFLGOBJ *)wi_FindObject( id, TMAX_MAXFLG, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストから該当するイベントフラグを取り除く.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! 待ちタスクキューを解放する.
	wi_WakeupDelResource( p->WaitQue );

	//! イベントフラグ･オブジェクト構造体を解放する.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグのセット.
 *
 *	@param	[in]	id		イベントフラグID番号.
 *	@param	[in]	setptn	セットするビットパターン.
 *
 *	@retval	エラーコード.
 */
ER		wi_SetEvFlag( INT id, UINT setptn )
{
	ER			ercd;
	WIFLGOBJ	*p;
	WITSKOBJ	*tsk,*next_link;
	UINT		tsk_flg,event_mode;
	BOOL		event_on;

	//! イベントフラグIDのオブジェクトを取得する.
	p = (WIFLGOBJ *)wi_FindObject( id, TMAX_MAXFLG, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 引数が不正な場合はエラーにする.
	if( setptn == 0 ){
		return E_PAR;
	}
	//! 指定されたフラグをセットする.
	p->FlgVal |= setptn;

	tsk = (WITSKOBJ *)(p->WaitQue);
	while( tsk ){
		event_on   = FALSE;
		tsk_flg    = (UINT)tsk->Param[0];
		event_mode = (UINT)tsk->Param[1];

		if( event_mode & TWF_ORW ){
			//! OR待ちの場合、いずれかのビットが一致すればイベントを発行する.
			if( (tsk_flg & p->FlgVal) != 0 ){
				event_on = TRUE;
			}
		}else{
			//! AND待ちの場合、全てのビットが一致すればイベントを発行する.
			if( (tsk_flg & p->FlgVal) == tsk_flg ){
				event_on = TRUE;
			}
		}
		//! 次のイベント待ちタスクを取り出す.
		next_link = tsk->QueLink;

		if( event_on ){
			//! イベント発生時のフラグパターンをタスク･オブジェクトに保存する.
			tsk->Param[2] = (VP)(p->FlgVal);

			//! フラグのクリア設定がされている場合はフラグをクリアする.
			if( (event_mode & TWF_CLR) != 0 || (p->Attribute & TA_CLR) != 0 ){
				p->FlgVal = 0;
			}
			//! イベント待ちをしているタスクを起床させる.
			wi_TaskWakeup( tsk->Hdr.Id, TTW_FLG, &(p->WaitQue) );
		}
		tsk = next_link;
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグのクリア.
 *
 *	@param	[in]	id		イベントフラグID番号.
 *	@param	[in]	clrptn	クリアするビットパターン.
 *
 *	@retval	エラーコード.
 */
ER		wi_ClearEvFlag( INT id, UINT clrptn )
{
	ER			ercd;
	WIFLGOBJ	*p;

	//! イベントフラグIDのオブジェクトを取得する.
	p = (WIFLGOBJ *)wi_FindObject( id, TMAX_MAXFLG, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 指定されたフラグをクリアする.
	p->FlgVal &= clrptn;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグ待ち.
 *
 *	@param	[in]	id			イベントフラグID番号.
 *	@param	[out]	flgptn		待ち解除時のビットパターンを格納する領域のポインタ.
 *	@param	[in]	waiptn		待ちビットパターン.
 *	@param	[in]	wfmode		待ちモード.
 *	@param	[in]	tmout		タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		wi_WaitEvFlag( INT id, UINT *flgptn, UINT waiptn, UINT wfmode, TMO tmout )
{
	WITSKOBJ	*tsk;
	WIFLGOBJ	*p;
	ER			ercd;
	BOOL		event_on;

	//! 引数が不正な場合はエラーにする.
	if( !flgptn || waiptn == 0 ){
		return E_PAR;
	}
	//! イベントフラグIDのオブジェクトを取得する.
	p = (WIFLGOBJ *)wi_FindObject( id, TMAX_MAXFLG, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	*flgptn  = 0;
	event_on = FALSE;
	if( wfmode & TWF_ORW ){
		//! OR待ちの場合、いずれかのビットが一致すれば「イベントあり」にする.
		if( (waiptn & p->FlgVal) != 0 ){
			event_on = TRUE;
		}
	}else{
		//! AND待ちの場合、全てのビットが一致すれば「イベントあり」にする.
		if( (waiptn & p->FlgVal) == waiptn ){
			event_on = TRUE;
		}
	}
	if( event_on ){
		//! イベント発生時のフラグパターンを戻り値にセットする.
		*flgptn = p->FlgVal;

		//! フラグのクリア設定がされている場合はフラグをクリアする.
		if( (wfmode & TWF_CLR) != 0 || (p->Attribute & TA_CLR) != 0 ){
			p->FlgVal = 0;
		}
		return E_OK;
	}
	//! 複数タスクの待ちを許可しない設定で、待ち行列に他のタスクがある場合はエラーにする.
	if( (p->Attribute & TA_WMUL) == 0 && p->WaitQue ){
		return E_ILUSE;
	}
	//! 自タスクのタスク･オブジェクトを取得する.
	tsk = wi_GetTaskObject( TSK_SELF );
	if( !tsk ){
		return E_CTX;
	}
	//! 待ちフラグパターンをタスク･オブジェクトに保存する.
	tsk->Param[0] = (VP)waiptn;
	tsk->Param[1] = (VP)wfmode;
	tsk->Param[2] = 0;

	//! イベントフラグが成立するまでタスクをスリープさせる.
	ercd = wi_TaskWait( id, TTW_FLG, tmout, p->Attribute, &(p->WaitQue) );

	//! イベント発生時のフラグパターンを戻り値にセットする.
	if( ercd == E_OK ){
		*flgptn = (UINT)(tsk->Param[2]);
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグ状態の参照.
 *
 *	@param	[in]	id		イベントフラグID番号.
 *	@param	[in]	sts		イベントフラグ状態を格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_RefarenceEvFlag( INT id, WIFLGSTAT *sts )
{
	ER			ercd;
	WIFLGOBJ	*p;

	//! イベントフラグIDのオブジェクトを取得する.
	p = (WIFLGOBJ *)wi_FindObject( id, TMAX_MAXFLG, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! イベントフラグの状態を構造体にセットする.
	sts->WaitId  = wi_GetWaitTaskListFirstId( p->WaitQue );
	sts->FlgVal  = p->FlgVal;
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
void	wi_AllReleaseEvFlag( INT id )
{
	WIFLGOBJ *p;

	for( p = (WIFLGOBJ *)ObjList; p; p = (WIFLGOBJ *)p->Hdr.Next ){

		//! 削除されるタスクを待ち行列から削除する.
		p->WaitQue = wi_DelWaitTaskList( id, p->WaitQue );
	}
}

/* End of file */
