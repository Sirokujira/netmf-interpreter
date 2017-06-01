/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_common.c
 *
 *	@brief	Windows版 iTRONサービスコール (その他共通関数).
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include <process.h>
#include "wi_common.h"
#include "wi_task.h"
#include "wi_cycle_handler.h"
#include "wi_alarm_handler.h"

/****************************************************************************
 *
 * ローカル関数定義.
 *
 ****************************************************************************/
static unsigned int __stdcall TimerTask( void* arg );

/****************************************************************************
 *
 * ローカル変数定義.
 *
 ****************************************************************************/
static HANDLE		CommMutex;			//!< サービスコール全体で使用するミューテックスのハンドル.
static HANDLE		TimerThread;		//!< 周期タイマ･スレッドのハンドル.
static BOOL			ExitFlag;			//!< TRUE = システムの終了要求.
static DWORDLONG	SystemTime;			//!< システム時刻.

/****************************************************************************/
/*!
 *	@brief	共通関数の初期処理.
 *
 *	@param	なし.
 *
 *	@retval	TRUE = OK. / FALSE = NG.
 */
BOOL	wi_CommonInit( void )
{
	unsigned int tid;

	CommMutex   = NULL;
	TimerThread = NULL;
	ExitFlag    = FALSE;
	SystemTime  = 0;

	//! ミューテックスを作成する.
	CommMutex = CreateMutex( NULL, FALSE, NULL );
	if( !CommMutex ){
		return FALSE;
	}
	//! 周期タイマ･スレッドを起動する.
	TimerThread = (HANDLE)_beginthreadex( NULL, 0, &TimerTask, NULL, 0, &tid );

	//! タスクの優先度を設定する.
	SetThreadPriority( TimerThread, THREAD_PRIORITY_ABOVE_NORMAL );

	return TRUE;
}

/****************************************************************************/
/*!
 *	@brief	共通関数の終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_CommonQuit( void )
{
	ExitFlag = TRUE;

	if( TimerThread ){
		//! スレッドが停止するのを確認する.
		wi_DormantThread( TimerThread, 1000 );

		//! 周期タイマ･スレッドのハンドルを解放する.
		CloseHandle( TimerThread );
	}

	//! 作成したミューテックスをクローズする.
	if( CommMutex ){
		CloseHandle( CommMutex );
		CommMutex = NULL;
	}
}

/****************************************************************************/
/*!
 *	@brief	ミューテックスをロックする.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_CommonLock( void )
{
	//! ミューテックスの所有権を獲得する.
	if( CommMutex ){
		WaitForSingleObject( CommMutex, INFINITE );
	}
}

/****************************************************************************/
/*!
 *	@brief	ミューテックスをアンロックする.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_CommonUnlock( void )
{
	//! ミューテックスの所有権を解放する.
	if( CommMutex ){
		ReleaseMutex( CommMutex );
	}
}

/****************************************************************************/
/*!
 *	@brief	スレッドを停止させる.
 *
 *	@param	[in]	hThread		スレッド･ハンドル.
 *	@param	[in]	wait_time	スレッド停止の待ち時間.
 *
 *	@retval	なし.
 */
void	wi_DormantThread( HANDLE hThread, DWORD wait_time )
{
	DWORD	i;
	DWORD	loop = (wait_time / 10) + 1;

	for( i = 0; i < loop; i++ ){
		//! スレッドの終了コードを取得する.
		DWORD code;
		if( !GetExitCodeThread( hThread, &code ) ){
			TerminateThread( hThread, 0 );
			return;
		}
		//! スレッドが停止している場合、処理を終了する.
		if( code != STILL_ACTIVE ){
			return;
		}
		Sleep( 10 );
	}
	//! スレッドを強制的に終了する.
	TerminateThread( hThread, 0 );
}

/****************************************************************************/
/*!
 *	@brief	システム時刻の設定.
 *
 *	@param	[in]	stime	設定する時刻.
 *
 *	@retval	なし.
 */
void	wi_SetSystemTime( DWORDLONG stime )
{
	SystemTime = stime;
}

/****************************************************************************/
/*!
 *	@brief	システム時刻の参照.
 *
 *	@param	なし.
 *
 *	@retval	システム時刻.
 */
DWORDLONG	wi_GetSystemTime( void )
{
	return SystemTime;
}

/****************************************************************************/
/*!
 *	@brief	自タスクのタスクIDを取得する.
 *
 *	@param	なし.
 *
 *	@retval	自タスクのタスクID.
 */
ID		wi_GetTaskId( void )
{
	return wi_GetActiveTaskId();
}

/****************************************************************************/
/*!
 *	@brief	オブジェクト･リストにオブジェクトを追加する.
 *
 *	@param	[in]	new_obj		追加するオブジェクト構造体のポインタ.
 *	@param	[out]	obj_list	オブジェクト構造体リストのポインタ.
 *
 *	@retval	なし.
 */
void	wi_AddObject( LPWIHDR new_obj, LPWIHDR *obj_list )
{
	LPWIHDR p = *obj_list;
	for( ; p && p->Next; p = p->Next ) ;

	if( !p ){
		*obj_list = new_obj;
	}else{
		p->Next = new_obj;
	}
}

/****************************************************************************/
/*!
 *	@brief	オブジェクト･リストからオブジェクトを削除する.
 *
 *	@param	[in]	del_obj		削除するオブジェクト構造体のポインタ.
 *	@param	[out]	obj_list	オブジェクト構造体リストのポインタ.
 *
 *	@retval	なし.
 */
void	wi_DelObject( LPWIHDR del_obj, LPWIHDR *obj_list )
{
	if( *obj_list ){
		//! リストの先頭のオブジェクトが削除するオブジェクトの場合.
		if( *obj_list == del_obj ){
			*obj_list =  del_obj->Next;
		}else{
			LPWIHDR p;
			for( p = *obj_list; p->Next; p = p->Next ){
				//! 一致するオブジェクトを見つけた場合、リストから削除する.
				if( p->Next == del_obj ){
					p->Next  = del_obj->Next;
					break;
				}
			}
		}
	}
}

/****************************************************************************/
/*!
 *	@brief	指定された識別子のオブジェクト構造体を取り出す.
 *
 *	@param	[in]	id			オブジェクト識別子.
 *	@param	[out]	obj_list	オブジェクト構造体リストのポインタ.
 *
 *	@retval	オブジェクト構造体のポインタ.
 */
void	*wi_GetObject( INT id, LPWIHDR obj_list )
{
	while( obj_list ){
		if( obj_list->Id == id ){
			return obj_list;
		}
		obj_list = obj_list->Next;
	}
	return NULL;
}

/****************************************************************************/
/*!
 *	@brief	オブジェクトを作成する.
 *
 *	@param	[in]	id			オブジェクトID番号.
 *	@param	[in]	max_id		オブジェクトID番号の最大値.
 *	@param	[in]	size		オブジェクトID番号の最大値.
 *	@param	[in]	param		オブジェクト生成情報のポインタ.
 *	@param	[in]	obj_list	オブジェクト･リストのポインタ.
 *	@param	[out]	ercd		エラーコードを格納する領域のポインタ.
 *
 *	@retval	作成したオブジェクトのポインタ.
 */
WIHDR	*wi_CreateObject( INT id, INT max_id, INT size, const void *param, WIHDR *obj_list, ER *ercd )
{
	WIHDR *p;

	//! 不正なIDの場合はエラーにする.
	if( id == 0 || id >= max_id ){
		*ercd = E_ID;
		return NULL;
	}
	//! 既に生成しているオブジェクトの場合はエラーにする.
	if( wi_GetObject( id, obj_list ) != NULL ){
		*ercd = E_OBJ;
		return NULL;
	}
	//! オブジェクト構造体を確保する.
	p = (WIHDR *)malloc( size );
	if( !p ){
		*ercd = E_NOMEM;
		return NULL;
	}
	//! オブジェクトの生成情報を保存する.
	memcpy( p, param, size );
	p->Id = id;
	*ercd = E_OK;
	return p;
}

/****************************************************************************/
/*!
 *	@brief	指定したID番号のオブジェクトをリストから検索する.
 *
 *	@param	[in]	id			オブジェクトID番号.
 *	@param	[in]	max_id		オブジェクトID番号の最大値.
 *	@param	[in]	obj_list	オブジェクト･リストのポインタ.
 *	@param	[out]	ercd		エラーコードを格納する領域のポインタ.
 *
 *	@retval	検出したオブジェクトのポインタ.
 */
WIHDR	*wi_FindObject( INT id, INT max_id, WIHDR *obj_list, ER *ercd )
{
	WIHDR *p;

	//! 不正なIDの場合はエラーにする.
	if( id == 0 || id >= max_id ){
		*ercd = E_ID;
		return NULL;
	}
	//! リストからオブジェクトを取得する.
	p = (WIHDR *)wi_GetObject( id, obj_list );
	if( !p ){
		*ercd = E_NOEXS;
		return NULL;
	}
	*ercd = E_OK;
	return p;
}

/****************************************************************************/
/*!
 *	@brief	リングバッファのカウンタをインクリメントする.
 *
 *	@param	[in]	pos		リングバッファのカウンタ.
 *	@param	[in]	size	リングバッファのサイズ.
 *
 *	@retval	インクリメント後のカウンタ値.
 */
DWORD	wi_IncRingPositon( DWORD pos, DWORD size )
{
	return ((pos + 1) >= size) ? 0 : (pos + 1);
}

/****************************************************************************/
/*!
 *	@brief	iTRONのタイマ時間をWindows用タイマ時間に変換する.
 *
 *	@param	[in]	tmout		iTRON用タイマ設定時間.
 *
 *	@retval	Windows用タイマの時間.
 */
DWORD	wi_CvtTimeOutValue( TMO tmout )
{
	switch( tmout ){
	  case TMO_POL : return 0;
	  case TMO_FEVR: return INFINITE;
	  default      : return tmout;
	}
}

/****************************************************************************/
/*!
 *	@brief	周期タイマ･タスク.
 *
 *	@param	[in]	arg		タスクリソース構造体のポインタ.
 *
 *	@retval	常に0を返す.
 */
static unsigned __stdcall TimerTask( void* arg )
{
	while( !ExitFlag ){

		DWORD btime,ntime,dtime;

		//! スリープ前のタイムカウンタを取得する.
		btime = GetTickCount();

		//! 一定時間スリープさせる.
//		timeBeginPeriod( 1 );
		Sleep( CYCLETIME );
//		timeEndPeriod ( 1 );

		//! スリープ後のタイムカウンタを取得する.
		ntime = GetTickCount();

		//! 実際にスリープした時間を計算する.
		if( ntime >= btime ){
			dtime = ntime - btime;
		}else{
			dtime = btime - ntime;
		}
		//! システム時刻をカウントアップする.
		SystemTime += dtime;

		//! 周期起動ハンドラを呼び出す.
		wi_CycleTimer( SystemTime );

		//! アラーム･ハンドラを呼び出す.
		wi_CallAlarmHandler( SystemTime );
	}
	_endthreadex( 0 );
	return 0;
}

/* End of file */
