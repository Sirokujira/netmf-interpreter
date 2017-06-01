/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_mail_box.c
 *
 *	@brief	Windows版 iTRONサービスコール (メールボックス).
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_mail_box.h"

/****************************************************************************
 *
 * ローカル変数定義.
 *
 ****************************************************************************/
static WIHDR	*ObjList;			//!< メールボックス･リストのポインタ.

/****************************************************************************/
/*!
 *	@brief	メールボックス管理の初期処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_InitMailBox( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	メールボックス管理の終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_QuitMailBox( void )
{
	WIHDR		*next_ptr;
	WIMBXOBJ	*p = (WIMBXOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! メールボックス･オブジェクト構造体を解放する.
		SAFE_RELEASE( p );

		//! 次のメールボックス･オブジェクト構造体を取り出す.
		p = (WIMBXOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	メールボックスの生成.
 *
 *	@param	[in]	id		メールボックスID番号.
 *	@param	[in]	obj		メールボックス･オブジェクト構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_CreateMailBox( INT id, const WIMBXOBJ *obj )
{
	ER			ercd;
	WIMBXOBJ	*p;

	//! 不正な引数の場合はエラーにする.
	if( (obj->Attribute & TA_MPRI) != 0 && (obj->MaxPriority == 0 || obj->MaxPriority > TMAX_MPRI) ){
		return E_PAR;
	}
	//! メールボックス･オブジェクトを作成する.
	p = (WIMBXOBJ *)wi_CreateObject( id, TMAX_MAXMBX, sizeof(WIMBXOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストにメールボックスを追加する.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	メールボックスの削除.
 *
 *	@param	[in]	id		メールボックスID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_DeleteMailBox( INT id )
{
	ER			ercd;
	WIMBXOBJ	*p;

	//! メールボックスIDのオブジェクトを取得する.
	p = (WIMBXOBJ *)wi_FindObject( id, TMAX_MAXMBX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストから該当するメールボックスを取り除く.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! 待ちタスクキューを解放する.
	wi_WakeupDelResource( p->WaitQue );

	//! メールボックス･オブジェクト構造体を解放する.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	メールボックスへの送信.
 *
 *	@param	[in]	id		メールボックスID番号.
 *	@param	[in]	msg		メッセージ･パケットのポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_SendMailBox( INT id, T_MSG *msg )
{
	ER			ercd;
	WIMBXOBJ	*p;
	T_MSG		*msg_ptr;

	//! メールボックスIDのオブジェクトを取得する.
	p = (WIMBXOBJ *)wi_FindObject( id, TMAX_MAXMBX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 不正な引数の場合はエラーにする.
	if( !msg ){
		return E_PAR;
	}
	msg->nextmsg = NULL;
	if( (p->Attribute & TA_MPRI) != 0 ){
		//! 優先度順にメッセージを格納する場合.
		if( !(p->MsgQue) ){
			//! メッセージキューにメッセージがない場合はメッセージキューの先頭に格納する.
			p->MsgQue = msg;
		}else
		if( p->MsgQue->msgpri > msg->msgpri ){
			//! メッセージキューの先頭メッセージより優先度が高い場合もメッセージキューの先頭に格納する.
			msg->nextmsg = p->MsgQue;
			p->MsgQue    = msg;
		}else{
			msg_ptr = p->MsgQue;
			while( msg_ptr ){
				if( !(msg_ptr->nextmsg) ){
					//! 次のメッセージがない場合はメッセージキューの最後にメッセージを格納する.
					msg_ptr->nextmsg = msg;
					break;
				}
				if( msg_ptr->nextmsg->msgpri > msg->msgpri ){
					//! 次のメッセージより優先度が高い場合、次のメッセージの前にメッセージを格納する.
					msg->nextmsg     = msg_ptr->nextmsg;
					msg_ptr->nextmsg = msg->nextmsg;
					break;
				}
				msg_ptr = msg_ptr->nextmsg;
			}
		}
	}else{
		//! メッセージ･パケット･リストにリンクされている最後のメッセージを探す.
		msg_ptr = p->MsgQue;
		while( msg_ptr ){
			if( !(msg_ptr->nextmsg) ){
				break;
			}
			msg_ptr = msg_ptr->nextmsg;
		}
		//! メッセージ･パケット･リストの最後に引数のメッセージ･パケットを追加する.
		if( msg_ptr ){
			msg_ptr->nextmsg = msg;
		}else{
			p->MsgQue = msg;
		}
	}
	//! メッセージ待ちをしているタスクがある場合はタスクを起床させる.
	if( p->WaitQue ){
		wi_TaskWakeup( p->WaitQue->Id, TTW_MBX, &(p->WaitQue) );
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	メールボックスからの受信.
 *
 *	@param	[in]	id		メールボックスID番号.
 *	@param	[out]	ppk_msg	メッセージ･パケットのアドレスを格納する領域のポインタ.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		wi_ReceiveMailBox( INT id, T_MSG **msg, TMO tmout )
{
	ER			ercd;
	WIMBXOBJ	*p;

	//! メールボックスIDのオブジェクトを取得する.
	p = (WIMBXOBJ *)wi_FindObject( id, TMAX_MAXMBX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 不正な引数の場合はエラーにする.
	if( !msg ){
		return E_PAR;
	}
	//! メッセージ･パケット･リストにメッセージがある場合はメッセージを取り出して終了する.
	if( p->MsgQue ){
		*msg      = p->MsgQue;
		p->MsgQue = p->MsgQue->nextmsg;
		return E_OK;
	}
	//! メッセージを受信するまでタスクをスリープさせる.
	ercd = wi_TaskWait( id, TTW_MBX, tmout, p->Attribute, &(p->WaitQue) );
	if( ercd == E_OK ){
		if( p->MsgQue ){
			*msg      = p->MsgQue;
			p->MsgQue = p->MsgQue->nextmsg;
		}
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	メールボックスの状態参照.
 *
 *	@param	[in]	id		メールボックスID番号.
 *	@param	[out]	sts		メールボックス状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_RefarenceMailBox( INT id, WIMBXSTAT *sts )
{
	ER			ercd;
	WIMBXOBJ	*p;

	//! メールボックスIDのオブジェクトを取得する.
	p = (WIMBXOBJ *)wi_FindObject( id, TMAX_MAXMBX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! メールボックスの状態を構造体にセットする.
	sts->WaitId  = wi_GetWaitTaskListFirstId( p->WaitQue );
	sts->NextMsg = p->MsgQue;
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
void	wi_AllReleaseMailBox( INT id )
{
	WIMBXOBJ *p;

	for( p = (WIMBXOBJ *)ObjList; p; p = (WIMBXOBJ *)p->Hdr.Next ){

		//! 削除されるタスクを待ち行列から削除する.
		p->WaitQue = wi_DelWaitTaskList( id, p->WaitQue );
	}
}

/* End of file */
