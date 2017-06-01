/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_data_queue.c
 *
 *	@brief	Windows版 iTRONサービスコール (データキュー).
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_data_queue.h"

/****************************************************************************
 *
 * ローカル変数定義.
 *
 ****************************************************************************/
static WIHDR	*ObjList;			//!< データキュー･リストのポインタ.

/****************************************************************************/
/*!
 *	@brief	データキューの初期処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_InitDataQueue( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	データキューの終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_QuitDataQueue( void )
{
	WIHDR		*next_ptr;
	WIDTQOBJ	*p = (WIDTQOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! データキューバッファを解放する.
		SAFE_RELEASE( p->QueBuf );

		//! データキュー･オブジェクト構造体を解放する.
		SAFE_RELEASE( p );

		//! 次のデータキュー･オブジェクト構造体を取り出す.
		p = (WIDTQOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	データキューの生成.
 *
 *	@param	[in]	id		データキューID番号.
 *	@param	[in]	obj		データキュー･オブジェクト構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_CreateDataQueue( INT id, const WIDTQOBJ *obj )
{
	ER			ercd;
	WIDTQOBJ	*p;

	//! データキュー･オブジェクトを作成する.
	p = (WIDTQOBJ *)wi_CreateObject( id, TMAX_MAXDTQ, sizeof(WIDTQOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	if( p->QueSize > 0 ){
		//! バッファFULL判定の為に1つ余計にバッファを確保する.
		p->QueSize++;

		//! データキューバッファを確保する.
		p->QueBuf = (DWORD *)malloc( sizeof(DWORD) * p->QueSize );
		if( !p->QueBuf ){
			SAFE_RELEASE( p );
			return E_NOMEM;
		}
		//! 確保したデータキューバッファをクリアする.
		memset( p->QueBuf, 0, sizeof(DWORD) * p->QueSize );
	}
	p->GetPos = 0;
	p->PutPos = 0;

	//! リストにデータキューを追加する.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	データキューの削除.
 *
 *	@param	[in]	id		データキューID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_DeleteDataQueue( INT id )
{
	ER			ercd;
	WIDTQOBJ	*p;

	//! データキューIDのオブジェクトを取得する.
	p = (WIDTQOBJ *)wi_FindObject( id, TMAX_MAXDTQ, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストから該当するデータキューを取り除く.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! 待ちタスクキューを解放する.
	wi_WakeupDelResource( p->SndWaitQue );
	wi_WakeupDelResource( p->RcvWaitQue );

	//! データキューバッファを解放する.
	SAFE_RELEASE( p->QueBuf );

	//! データキュー･オブジェクト構造体を解放する.
	SAFE_RELEASE( p );
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	データキューへの送信.
 *
 *	@param	[in]	id		データキューID番号.
 *	@param	[in]	data	データキューに送信するデータ.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		wi_SendDataQueue( INT id, DWORD data, TMO tmout )
{
	WITSKOBJ	*tsk;
	WIDTQOBJ	*p;
	DWORD		pos;
	ER			ercd;

	//! データキューIDのオブジェクトを取得する.
	p = (WIDTQOBJ *)wi_FindObject( id, TMAX_MAXDTQ, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! データキューバッファを確保していない場合.
	if( p->QueSize == 0 || !p->QueBuf ){

		if( p->RcvWaitQue ){
			tsk = (WITSKOBJ *)(p->RcvWaitQue);

			//! メッセージを受信タスクに保存する.
			tsk->Param[0] = (VP)data;

			//! メッセージ待ちをしているタスクがある場合はタスクを起床させる.
			wi_TaskWakeup( tsk->Hdr.Id, TTW_RDTQ, &(p->RcvWaitQue) );
			return E_OK;
		}else{
			//! メッセージを送信タスク(自タスク)に保存する.
			tsk = wi_GetTaskObject( TSK_SELF );
			if( tsk ){
				tsk->Param[0] = (VP)data;
			}
			//! 受信タスクが現れるまでタスクをスリープさせる.
			ercd = wi_TaskWait( id, TTW_SDTQ, tmout, p->Attribute, &(p->SndWaitQue) );
			return ercd;
		}
	}
	pos = wi_IncRingPositon( p->PutPos, p->QueSize );
	if( pos == p->GetPos ){
		//! データキューバッファが空くまでタスクをスリープさせる.
		ercd = wi_TaskWait( id, TTW_SDTQ, tmout, p->Attribute, &(p->SndWaitQue) );
		if( ercd != E_OK ){
			return ercd;
		}
	}
	//! データキューに送信データを格納する.
	p->QueBuf[p->PutPos] = data;

	//! データキューの書込み位置を更新する.
	p->PutPos = pos;

	//! データ受信待ちをしているタスクがある場合はタスクを起床させる.
	if( p->RcvWaitQue ){
		wi_TaskWakeup( p->RcvWaitQue->Id, TTW_RDTQ, &(p->RcvWaitQue) );
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	データキューへの強制送信.
 *
 *	@param	[in]	id		データキューID番号.
 *	@param	[in]	data	データキューに送信するデータ.
 *
 *	@retval	エラーコード.
 */
ER		wi_ForceSendDataQueue( INT id, DWORD data )
{
	ER			ercd;
	WIDTQOBJ	*p;
	DWORD		pos;

	//! データキューIDのオブジェクトを取得する.
	p = (WIDTQOBJ *)wi_FindObject( id, TMAX_MAXDTQ, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! データキューバッファを確保していない場合はエラーにする.
	if( p->QueSize == 0 ){
		return E_ILUSE;
	}
	//! データキューに空きがない場合はデータキューの先頭データを廃棄する.
	pos = wi_IncRingPositon( p->PutPos, p->QueSize );
	if( pos == p->GetPos ){
		p->GetPos = wi_IncRingPositon( p->GetPos, p->QueSize );
	}
	//! データキューのデータ送信処理を呼び出す.
	return wi_SendDataQueue( id, data, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	データキューからの受信.
 *
 *	@param	[in]	id		データキューID番号.
 *	@param	[out]	data	データキューから受信したデータを格納する領域のポインタ.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		wi_ReceiveDataQueue( INT id, DWORD *data, TMO tmout )
{
	ER			ercd;
	WIDTQOBJ	*p;
	WITSKOBJ	*tsk;

	//! データキューIDのオブジェクトを取得する.
	p = (WIDTQOBJ *)wi_FindObject( id, TMAX_MAXDTQ, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 引数が不正な場合はエラーにする.
	if( !data ){
		return E_PAR;
	}
	//! データキューバッファを確保していない場合.
	if( p->QueSize == 0 || !p->QueBuf ){

		if( p->SndWaitQue ){
			tsk = (WITSKOBJ *)(p->SndWaitQue);

			//! 送信メッセージを取り出す.
			*data = (DWORD)(tsk->Param[0]);

			//! メッセージ受信先を待っているタスクを起床させる.
			wi_TaskWakeup( tsk->Hdr.Id, TTW_SDTQ, &(p->SndWaitQue) );
			return E_OK;
		}else{
			//! メッセージが送信されるまでタスクをスリープさせる.
			ercd = wi_TaskWait( id, TTW_RDTQ, tmout, p->Attribute, &(p->RcvWaitQue) );
			if( ercd == E_OK ){
				//! 送信メッセージを取り出す.
				tsk = wi_GetTaskObject( TSK_SELF );
				if( tsk ){
					*data = (DWORD)(tsk->Param[0]);
				}
			}
			return ercd;
		}
	}
	//! データキューにデータがある場合、データを取り出して終了する.
	if( p->GetPos != p->PutPos ){

		//! データキューの先頭からデータを取り出す.
		*data = p->QueBuf[p->GetPos];

		//! データキューの読み出し位置を更新する.
		p->GetPos = wi_IncRingPositon( p->GetPos, p->QueSize );

		//! バッファが空くのを待っているタスクがある場合はタスクを起床させる.
		if( p->SndWaitQue ){
			wi_TaskWakeup( p->SndWaitQue->Id, TTW_SDTQ, &(p->SndWaitQue) );
		}
		return E_OK;
	}
	//! メッセージを受信するまでタスクをスリープさせる.
	ercd = wi_TaskWait( id, TTW_RDTQ, tmout, p->Attribute, &(p->RcvWaitQue) );
	if( ercd == E_OK ){
		if( p->GetPos != p->PutPos ){
			//! データキューの先頭からデータを取り出す.
			*data = p->QueBuf[p->GetPos];

			//! データキューの読み出し位置を更新する.
			p->GetPos = wi_IncRingPositon( p->GetPos, p->QueSize );
		}
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	データキューの状態参照.
 *
 *	@param	[in]	id		データキューID番号.
 *	@param	[out]	sts		データキュー状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_RefarenceDataQueue( INT id, WIDTQSTAT *sts )
{
	ER			ercd;
	WIDTQOBJ	*p;
	DWORD		cnt;

	//! データキューIDのオブジェクトを取得する.
	p = (WIDTQOBJ *)wi_FindObject( id, TMAX_MAXDTQ, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! データキューに入っているデータの個数を計算する.
	if( p->GetPos <= p->PutPos ){
		cnt = p->PutPos - p->GetPos;
	}else{
		cnt = (p->QueSize + p->PutPos) - p->GetPos;
	}
	//! データキューの状態を構造体にセットする.
	sts->SndWaitId = wi_GetWaitTaskListFirstId( p->SndWaitQue );
	sts->RcvWaitId = wi_GetWaitTaskListFirstId( p->RcvWaitQue );
	sts->DataCnt   = cnt;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	削除されるタスクを待ち行列から削除する.
 *
 *	@param	[in]	id	削除されるタスクID番号.
 *
 *	@retval	なし.
 */
void	wi_AllReleaseDataQueue( INT id )
{
	WIDTQOBJ *p;

	for( p = (WIDTQOBJ *)ObjList; p; p = (WIDTQOBJ *)p->Hdr.Next ){

		//! 削除されるタスクを待ち行列から削除する.
		p->SndWaitQue = wi_DelWaitTaskList( id, p->SndWaitQue );
		p->SndWaitQue = wi_DelWaitTaskList( id, p->SndWaitQue );
	}
}

/* End of file */
