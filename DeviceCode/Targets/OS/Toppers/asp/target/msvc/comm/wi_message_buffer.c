/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_message_buffer.c
 *
 *	@brief	Windows版 iTRONサービスコール (メッセージバッファ).
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_message_buffer.h"

/****************************************************************************
 *
 * ローカル関数定義.
 *
 ****************************************************************************/
static void		RestoreMessageData( WIMBFOBJ *p );
static INT		GetNextMessageSize( WIMBFOBJ *p );
static INT		GetFreeSize( WIMBFOBJ *p );
static BOOL		PutMesageData( WIMBFOBJ *p, BYTE* msg, INT len );
static INT		GetMessageData( WIMBFOBJ *p, BYTE* msg );

/****************************************************************************
 *
 * ローカル変数定義.
 *
 ****************************************************************************/
static WIHDR	*ObjList;		//!< メッセージバッファ･リストのポインタ.

/****************************************************************************/
/*!
 *	@brief	メッセージバッファの初期処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_InitMsgBuffer( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファの終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_QuitMsgBuffer( void )
{
	WIHDR		*next_ptr;
	WIMBFOBJ	*p = (WIMBFOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! メッセージバッファを解放する.
		SAFE_RELEASE( p->MsgBuf );

		//! メッセージバッファ･オブジェクト構造体を解放する.
		SAFE_RELEASE( p );

		//! 次のメッセージバッファ･オブジェクト構造体を取り出す.
		p = (WIMBFOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファの生成.
 *
 *	@param	[in]	id		メッセージバッファID番号.
 *	@param	[in]	obj		メッセージバッファ･オブジェクト構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_CreateMsgBuffer( INT id, const WIMBFOBJ *obj )
{
	ER			ercd;
	WIMBFOBJ	*p;

	//! 不正な引数の場合はエラーにする.
	if( obj->MaxMsg == 0 ){
		return E_PAR;
	}
	//! メッセージバッファ･オブジェクトを作成する.
	p = (WIMBFOBJ *)wi_CreateObject( id, TMAX_MAXMBF, sizeof(WIMBFOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! メッセージバッファを確保する.
	if( p->MsgSize > 0 ){
		p->MsgBuf = (BYTE *)malloc( p->MsgSize );
		if( !p->MsgBuf ){
			SAFE_RELEASE( p );
			return E_NOMEM;
		}
		//! 確保したメッセージバッファをクリアする.
		memset( p->MsgBuf, 0, p->MsgSize );
	}
	p->GetPos = 0;
	p->PutPos = 0;

	//! リストにメッセージバッファを追加する.
	wi_AddObject( (WIHDR *)p, &ObjList );

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファの削除.
 *
 *	@param	[in]	id		メッセージバッファID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_DeleteMsgBuffer( INT id )
{
	ER			ercd;
	WIMBFOBJ	*p;

	//! メッセージバッファIDのオブジェクトを取得する.
	p = (WIMBFOBJ *)wi_FindObject( id, TMAX_MAXMBF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストから該当するメッセージバッファを取り除く.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! 待ちタスクキューを解放する.
	wi_WakeupDelResource( p->SndWaitQue );
	wi_WakeupDelResource( p->RcvWaitQue );

	//! メッセージバッファを解放する.
	SAFE_RELEASE( p->MsgBuf );

	//! メッセージバッファ･オブジェクト構造体を解放する.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	メッセージ･バッファへの送信.
 *
 *	@param	[in]	id		メッセージバッファID番号.
 *	@param	[in]	msg		メッセージのポインタ.
 *	@param	[in]	size	メッセージのサイズ.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		wi_SendMsgBuffer( INT id, VP msg, INT size, TMO tmout )
{
	ER			ercd;
	WIMBFOBJ	*p;
	WITSKOBJ	*tsk1,*tsk2;

	//! メッセージバッファIDのオブジェクトを取得する.
	p = (WIMBFOBJ *)wi_FindObject( id, TMAX_MAXMBF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 引数が不正な場合はエラーにする.
	if( !msg || !size ){
		return E_PAR;
	}
	//! メッセージ待ちをしているタスクがある場合.
	if( p->RcvWaitQue ){

		//! メッセージ待ちをしているタスクにメッセージを渡す.
		tsk1 = (WITSKOBJ *)(p->RcvWaitQue);
		if( tsk1->Param[0] ){
			memcpy( tsk1->Param[0], msg, size );
			tsk1->Param[1] = (VP)size;
		}
		//! メッセージ待ちをしているタスクを起床する.
		wi_TaskWakeup( tsk1->Hdr.Id, TTW_RMBF, &(p->RcvWaitQue) );
		return E_OK;
	}
	//! 自タスクのタスクコンテキストを取り出す.
	tsk1 = wi_GetTaskObject( TSK_SELF );

	//! 非タスクコンテキストからの呼び出しの場合はエラーにする.
	if( !tsk1 ){
		return E_CTX;
	}
	//! 送信待ちのタスクがある場合.
	if( p->SndWaitQue ){

		/*!
		 * 待ち行列がタスク優先度順の場合、待ち行列の先頭のタスクの優先度より
		 * 今回のタスク(自タスク)の優先度が大きいければ、メッセージバッファに
		 * 待ち行列のタスクよりも先に送信メッセージを格納する.
		 */
		if( p->SndAttr & TA_TPRI ){
			tsk2 = (WITSKOBJ *)(p->SndWaitQue);
			if( tsk1->TaskPri > tsk2->TaskPri ){
				if( PutMesageData( p, msg, size ) ){
					return E_OK;
				}
			}
		}
	}else{
		//! メッセージバッファの最後に送信メッセージを格納する.
		if( PutMesageData( p, msg, size ) ){
			return E_OK;
		}
	}
	//! タスクコンテキストに送信メッセージを格納しておく.
	tsk1->Param[0] = msg;
	tsk1->Param[1] = (VP)size;

	//! バッファが空くまでタスクをスリープさせる.
	return wi_TaskWait( id, TTW_SMBF, tmout, p->SndAttr, &(p->SndWaitQue) );
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファからの受信.
 *
 *	@param	[in]	id		メッセージバッファID番号.
 *	@param	[out]	msg		メッセージを格納する領域のポインタ.
 *	@param	[out]	size	メッセージ･サイズを格納する領域のポインタ.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		wi_ReceiveMsgBuffer( INT id, VP msg, INT *size, TMO tmout )
{
	ER			ercd;
	WIMBFOBJ	*p;
	WITSKOBJ	*tsk;

	//! メッセージバッファIDのオブジェクトを取得する.
	p = (WIMBFOBJ *)wi_FindObject( id, TMAX_MAXMBF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 引数が不正な場合はエラーにする.
	if( !msg || !size ){
		return E_PAR;
	}
	//! メッセージバッファからメッセージを取り出す.
	*size = GetMessageData( p, (BYTE *)msg );
	if( *size > 0 ){
		//! メッセージバッファが空いたので送信待ちをしているメッセージをバッファに書き込む.
		RestoreMessageData( p );
		return E_OK;
	}
	/*!
	 * メッセージ送信待ちをしているタスクがある場合、
	 * メッセージ送信タスクから直接メッセージを受け取る.
	 */
	if( p->SndWaitQue ){

		//! メッセージ送信待ちをしているタスクのコンテキストを取り出す.
		tsk = (WITSKOBJ *)(p->SndWaitQue);

		if( tsk->Param[0] ){
			//! メッセージ送信タスクから直接メッセージをコピーする.
			memcpy( msg, tsk->Param[0], (INT)(tsk->Param[1]) );
			tsk->Param[0] = NULL;
			tsk->Param[1] = 0;

			/*!
			 * メッセージバッファに書き込めるかもしれないので
			 * 送信待ちをしているメッセージをバッファに書き込む.
			 */
			RestoreMessageData( p );

			return E_OK;
		}else{
			/*!
			 * 送信メッセージが無いのに送信待ちをしているタスクがあった場合、
			 * 送信待ちをしているタスクは起床させる.
			 */
			wi_TaskWakeup( tsk->Hdr.Id, TTW_SMBF, &(p->SndWaitQue) );
			return E_SYS;
		}
	}
	//! 自タスクのタスクコンテキストにメッセージ格納バッファのポインタをセットする.
	tsk = wi_GetTaskObject( TSK_SELF );
	if( !tsk ){
		return E_CTX;
	}
	tsk->Param[0] = msg;
	tsk->Param[1] = 0;

	//! メッセージを受信するまでタスクをスリープさせる.
	ercd = wi_TaskWait( id, TTW_RMBF, tmout, p->RcvAttr, &(p->RcvWaitQue) );
	if( ercd == E_OK ){
		*size = (INT)tsk->Param[1];
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファの状態参照.
 *
 *	@param	[in]	id		メッセージバッファID番号.
 *	@param	[out]	sts		メッセージバッファ状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_RefarenceMsgBuffer( INT id, WIMBFSTAT *sts )
{
	ER			ercd;
	WIMBFOBJ	*p;

	//! メッセージバッファIDのオブジェクトを取得する.
	p = (WIMBFOBJ *)wi_FindObject( id, TMAX_MAXMBF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! メッセージバッファの状態を構造体にセットする.
	sts->SndWaitId = wi_GetWaitTaskListFirstId( p->SndWaitQue );
	sts->RcvWaitId = wi_GetWaitTaskListFirstId( p->RcvWaitQue );
	sts->MsgSize   = GetNextMessageSize( p );
	sts->FreeSize  = GetFreeSize( p );
	sts->ExtInfo   = p->ExtInfo;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	メッセージ送信待ちをしているデータをバッファに書き込む.
 *
 *	@param	[in]	p		メッセージバッファ･オブジェクトのポインタ.
 *
 *	@retval	なし.
 */
static void		RestoreMessageData( WIMBFOBJ *p )
{
	WITSKOBJ *tsk;

	tsk = (WITSKOBJ *)(p->SndWaitQue);
	while( tsk ){

		//! メッセージがバッファに書き込めない場合は処理を終了にする.
		if( tsk->Param[0] ){
			if( !PutMesageData( p, (BYTE *)(tsk->Param[0]), (INT)(tsk->Param[1]) ) ){
				break;
			}
		}
		//! メッセージの送信を待っているタスクを起床させる.
		wi_TaskWakeup( tsk->Hdr.Id, TTW_SMBF, NULL );

		//! 待ち行列から次のタスクを取り出す.
		tsk = tsk->QueLink;
	}
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファの先頭メッセージのサイズをを取得する.
 *
 *	@param	[in]	p		メッセージバッファ･オブジェクトのポインタ.
 *
 *	@retval	メッセージバッファの先頭メッセージのサイズ.
 */
static INT		GetNextMessageSize( WIMBFOBJ *p )
{
	INT i,pos;
	INT msg_size = 0;

	if( p->GetPos == p->PutPos || !p->MsgBuf ){
		msg_size = 0;
	}else{
		pos = p->GetPos;
		for( i = 0; i < 4; i++ ){
			//! メッセージのサイズを1バイトづつ取り出す.
			msg_size = (msg_size << 8) + ((INT)p->MsgBuf[pos] & 0xFF);

			pos = wi_IncRingPositon( pos, p->MsgSize );
		}
	}
	return msg_size;
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファの空き領域のサイズを取得する.
 *
 *	@param	[in]	p		メッセージバッファ･オブジェクトのポインタ.
 *
 *	@retval	メッセージバッファの空き領域のサイズ.
 */
static INT		GetFreeSize( WIMBFOBJ *p )
{
	INT free_size = 0;

	if( p->GetPos == p->PutPos ){
		if( !p->MsgBuf || p->MsgSize == 0 ){
			free_size = 0;
		}else{
			free_size = p->MsgSize - sizeof(DWORD);
		}
	}else{
		if( p->GetPos <= p->PutPos ){
			free_size = p->MsgSize - (p->PutPos - p->GetPos) - sizeof(DWORD);
		}else{
			free_size = (p->GetPos - p->PutPos) - sizeof(DWORD);
		}
	}
	if( free_size < 0 ){
		free_size = 0;
	}
	return free_size;
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファにメッセージを格納する.
 *
 *	@param	[in]	p		メッセージバッファ･オブジェクトのポインタ.
 *	@param	[in]	msg		メッセージを格納した領域のポインタ.
 *	@param	[in]	len		メッセージのサイズ.
 *
 *	@retval	TRUE = OK. / FALSE = NG.
 */
static BOOL	PutMesageData( WIMBFOBJ *p, BYTE* msg, INT len )
{
	INT i;
	INT free_size;

	//! メッセージバッファに空きがない場合は処理を終了する.
	free_size = GetFreeSize( p );
	if( free_size < len ){
		return FALSE;
	}
	/*!
	 * メッセージ･サイズの途中でリングバッファを折り返えすかもしれないので
	 * メッセージ･サイズを1バイトづつバッファに格納する.
	 */
	for( i = 0; i < 4; i++ ){
		static int shift[4] = { 24, 16, 8, 0 };

		//! メッセージのサイズを1バイトづつ格納する.
		p->MsgBuf[p->PutPos] = (BYTE)((((DWORD)len) >> shift[i]) & 0xFF);

		//! バッファの書き込み位置を更新する.
		p->PutPos = wi_IncRingPositon( p->PutPos, p->MsgSize );
	}
	//! メッセージがリングバッファを折り返す場合は2回に分けてメッセージを格納する.
	if( (p->PutPos + len) > p->MsgSize ){
		DWORD size1,size2;

		//! リングバッファの最後にメッセージの先頭データをコピーする.
		size1 = p->MsgSize - p->PutPos;
		memcpy( &p->MsgBuf[p->PutPos], msg, size1 );

		//! リングバッファの先頭に残りのメッセージをコピーする.
		size2 = len - size1;
		memcpy( p->MsgBuf, &msg[size1], size2 );

		//! バッファの書き込み位置を更新する.
		p->PutPos = size2;
	}else{
		//! バッファにメッセージをコピーする.
		memcpy( &p->MsgBuf[p->PutPos], msg, len );

		//! バッファの書き込み位置を更新する.
		p->PutPos += len;
	}
	return (INT)len;
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファからメッセージを取り出す.
 *
 *	@param	[in]	p		メッセージバッファ･オブジェクトのポインタ.
 *	@param	[out]	msg		メッセージを格納する領域のポインタ.
 *
 *	@retval	取り出したメッセージのサイズ.
 */
static INT	GetMessageData( WIMBFOBJ *p, BYTE* msg )
{
	int		i;
	DWORD	len;

	//! メッセージバッファにデータがない場合は処理を終了する.
	if( !p->MsgBuf || p->GetPos == p->PutPos ){
		return 0;
	}
	/*!
	 * メッセージ･サイズの途中でリングバッファを折り返したかもしれないので
	 * メッセージ･サイズを1バイトづつバッファから取り出す.
	 */
	len = 0;
	for( i = 0; i < 4; i++ ){
		//! メッセージのサイズを1バイトづつ取り出す.
		len = (len << 8) + ((DWORD)p->MsgBuf[p->GetPos] & 0x000000FF);

		//! バッファの読み出し位置を更新する.
		p->GetPos = wi_IncRingPositon( p->GetPos, p->MsgSize );
	}
	//! メッセージがリングバッファを折り返す場合は2回に分けてメッセージを取り出す.
	if( (p->GetPos + len) > p->MsgSize ){
		DWORD size1,size2;

		//! リングバッファの最後からメッセージの先頭データをコピーする.
		size1 = p->MsgSize - p->GetPos;
		memcpy( msg, &p->MsgBuf[p->GetPos], size1 );

		//! リングバッファの先頭から残りのメッセージをコピーする.
		size2 = len - size1;
		memcpy( &msg[size1], p->MsgBuf, size2 );

		//! バッファの読み出し位置を更新する.
		p->GetPos = size2;
	}else{
		//! バッファからメッセージをコピーする.
		memcpy( msg, &p->MsgBuf[p->GetPos], len );

		//! バッファの読み出し位置を更新する.
		p->GetPos += len;
	}
	return (INT)len;
}

/****************************************************************************/
/*!
 *	@brief	削除されるタスクを待ち行列から削除する.
 *
 *	@param	[in]	id		削除されるタスクID番号.
 *
 *	@retval	なし.
 */
void	wi_AllReleaseMsgBuffer( INT id )
{
	WIMBFOBJ *p;

	for( p = (WIMBFOBJ *)ObjList; p; p = (WIMBFOBJ *)p->Hdr.Next ){

		//! 削除されるタスクを待ち行列から削除する.
		p->SndWaitQue = wi_DelWaitTaskList( id, p->SndWaitQue );
		p->RcvWaitQue = wi_DelWaitTaskList( id, p->RcvWaitQue );
	}
}

/* End of file */
