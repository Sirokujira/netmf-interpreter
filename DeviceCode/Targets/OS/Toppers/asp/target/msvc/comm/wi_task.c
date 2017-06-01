/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_task.c
 *
 *	@brief	Windows版 iTRONサービスコール (タスク機能).
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include <process.h>
#include "wi_task.h"
#include "wi_semaphore.h"
#include "wi_event_flag.h"
#include "wi_mail_box.h"
#include "wi_data_queue.h"
#include "wi_mutex.h"
#include "wi_message_buffer.h"
#include "wi_rendezvous_port.h"
#include "wi_fixed_mempool.h"
#include "wi_variable_mempool.h"

/****************************************************************************
 *
 * ローカル関数定義.
 *
 ****************************************************************************/
static unsigned int __stdcall UserTask( void* arg );
static int			ConvertPriority( PRI tskpri );
static WITSKOBJ		*FindTaskObject( INT id, ER *ercd );

/****************************************************************************
 *
 * ローカル変数定義.
 *
 ****************************************************************************/
static WIHDR		*ObjList;		//!< タスク･リストのポインタ.

/****************************************************************************/
/*!
 *	@brief	タスク管理の初期処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_InitTask( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	タスク管理の終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_QuitTask( void )
{
	WITSKOBJ *p = (WITSKOBJ *)ObjList;
	while( p ){
		WIHDR *next_ptr;
		next_ptr = p->Hdr.Next;

		//! イベント･ハンドルを解放する.
		if( p->hEvent ){
			CloseHandle( p->hEvent );
		}
		if( p->hThread ){
			//! スレッドが停止するのを確認する.
			wi_DormantThread( p->hThread, 10 );

			//! スレッド･ハンドルを解放する.
			CloseHandle( p->hThread );
		}
		//! タスク･オブジェクトを解放する.
		SAFE_RELEASE( p );

		//! 次のタスク･オブジェクトを取り出す.
		p = (WITSKOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	タスクを生成する.
 *
 *	@param	[in]	id		タスクID番号.
 *	@param	[in]	obj		タスク･オブジェクト構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER	wi_CreateTask( INT id, const WITSKOBJ *obj )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! タスク･オブジェクトを作成する.
	p = (WITSKOBJ *)wi_CreateObject( id, TMAX_MAXTSK, sizeof(WITSKOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 引数が不正な場合はエラーにする.
	if( !obj->TaskAdr || obj->InitPri == 0 ){
		return E_PAR;
	}
	//! タスクの状態を「休止中」にする.
	p->TaskState = TTS_DMT;

	//! イベント･ハンドルを作成する.
	p->hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	if( !p->hEvent ){
		SAFE_RELEASE( p );
		return E_SYS;
	}
	//! リストにタスクを追加する.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	ユーザータスクを起動する.
 *
 *	@param	[in]	arg		タスク･オブジェクト構造体のポインタ.
 *
 *	@retval	常に0を返す.
 */
static unsigned __stdcall UserTask( void* arg )
{
	WITSKOBJ *p = (WITSKOBJ *)arg;
	if( p ){
		//! タスクの状態を「実行中」にする.
		p->TaskState = TTS_RUN;

		//! ユーザータスクを呼び出す.
		p->TaskAdr( p->StartCode );

		//! タスクの状態を「休止中」にする.
		p->TaskState = TTS_DMT;
	}
	_endthreadex( 0 );
	return 0;
}

/****************************************************************************/
/*!
 *	@brief	タスクの削除.
 *
 *	@param	[in]	id		タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_DeleteTask( INT id )
{
	WITSKOBJ	*p      = (WITSKOBJ *)ObjList;
	WIHDR		**b_ptr = &ObjList;

	//! 自タスクは削除できない.
	if( id == TSK_SELF ){
		return E_OBJ;
	}
	//! 不正なタスクIDの場合はエラーにする.
	if( id >= TMAX_MAXTSK ){
		return E_ID;
	}
	while( p ){
		//! 指定されたIDと一致するタスクを見つけた場合、タスクをクローズする.
		if( p->Hdr.Id == id ){

			//! スレッドが休止状態でない場合は削除しない.
			if( p->TaskState != TTS_DMT ){
				return E_OBJ;
			}
			//! リストから該当するタスクを取り除く.
			*b_ptr = (WIHDR *)(p->Hdr.Next);

			if( p->hThread ){
				//! スレッドが停止していることを確認する.
				wi_DormantThread( p->hThread, 10 );

				//! スレッド･ハンドルを解放する.
				CloseHandle( p->hThread );
				 p->hThread = NULL;
			}
			//! イベント･ハンドルを解放する.
			if( p->hEvent ){
				CloseHandle( p->hEvent );
				p->hEvent = NULL;
			}
			//! 待ち行列からタスクを削除する.
			wi_AllReleaseSemaphore( id );
			wi_AllReleaseEvFlag( id );
			wi_AllReleaseMailBox( id );
			wi_AllReleaseDataQueue( id );
			wi_AllReleaseMutex( id );
			wi_AllReleaseMsgBuffer( id );
			wi_AllReleaseRendPort( id );

			//! メモリプールから獲得したメモリブロックを返却する.
			wi_AllReleaseFixedMemPool( id );
			wi_AllReleaseVarMemPool( id );

			//! タスク構造体を解放する.
			SAFE_RELEASE( p );
			return E_OK;
		}
		//! リストから次のタスクを取り出す.
		b_ptr = &(p->Hdr.Next);
		p     = (WITSKOBJ *)(p->Hdr.Next);
	}
	return E_NOEXS;
}

/****************************************************************************/
/*!
 *	@brief	タスクの起動.
 *
 *	@param	[in]	id			タスクID番号.
 *	@param	[in]	start_code	タスク起動コード.
 *	@param	[in]	exist_stcd	TRUE = タスク起動コードあり.
 *
 *	@retval	エラーコード.
 */
ER		wi_StartTask( INT id, DWORD start_code, BOOL exist_stcd )
{
	WITSKOBJ *p;

	//! タスクIDのオブジェクトを取得する.
	p = wi_GetTaskObject( id );
	if( !p ){
		return E_ID;
	}
	if( p->hThread ){
		//! スレッドが終了しているかどうかを調べる.
		DWORD code;
		if( !GetExitCodeThread( p->hThread, &code ) ){
			return E_SYS;
		}
		//! スレッドが起動中の場合.
		if( code == STILL_ACTIVE ){
			if( !exist_stcd ){
				//! act_tsk(),iact_tsk()からの呼び出しの場合は起動要求回数をカウントアップする.
				if( p->ActiveCnt + 1 > TMAX_ACTCNT ){
					return E_QOVR;
				}
				//! 起動要求回数をカウントアップする.
				p->ActiveCnt++;
				return E_OK;
			}else{
				//! sta_tsk()からの呼び出しの場合はエラーにする.
				return E_OBJ;
			}
		}
		//! 休止中のスレッドのスレッドハンドルをクローズする.
		CloseHandle( p->hThread );
		p->hThread = NULL;
	}
	p->SuspendCnt = 0;
	p->WakeupCnt  = 0;
	p->ActiveCnt  = 0;

	if( exist_stcd ){
		//! sta_tsk()からの呼び出しの場合は引数の起動コードを使用する.
		p->StartCode = start_code;
	}else{
		//! act_tsk(),iact_tsk()からの呼び出しの場合はcre_tsk()時の拡張情報を起動コードとする.
		p->StartCode = (DWORD)p->ExtInfo;
	}

	//! タスクの状態を「実行可能状態」にする.
	p->TaskState = TTS_RDY;

	//! スレッドを休止状態で起動する.
	p->hThread = (HANDLE)_beginthreadex( NULL, 0, &UserTask, p, CREATE_SUSPENDED, &(p->ThreadId) );

	//! スレッドの優先度を設定する.
	SetThreadPriority( p->hThread, ConvertPriority( p->InitPri ) );

	//! スレッドの休止状態を解除する.
	if( ResumeThread( p->hThread ) == -1 ){
		return E_SYS;
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	タスク起動要求のキャンセル.
 *
 *	@param	[in]	id		タスクID番号.
 *
 *	@retval	キューイングされていた起動要求回数またはエラーコード.
 */
int		wi_CancelStartReq( INT id )
{
	int			cnt;
	ER			ercd;
	WITSKOBJ	*p;

	//! タスクIDのオブジェクトを取得する.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	//! 起動要求回数を取り出す.
	cnt = p->ActiveCnt;

	//! 起動要求回数をクリアする.
	p->ActiveCnt = 0;

	return cnt;
}

/****************************************************************************/
/*!
 *	@brief	自タスクの終了.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_ExitTask( void )
{
	WITSKOBJ *p;

	wi_CommonLock();

	//! 自タスクのタスク･オブジェクトを取得する.
	p = wi_GetTaskObject( TSK_SELF );
	if( p ){
		p->TaskState = TTS_DMT;
	}
	wi_CommonUnlock();

	_endthreadex( 0 );
}

/****************************************************************************/
/*!
 *	@brief	自タスクの終了と削除.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_ExpendTask( void )
{
	WITSKOBJ *p;

	wi_CommonLock();

	//! 自タスクのタスク･オブジェクトを取得する.
	p = wi_GetTaskObject( TSK_SELF );
	if( p ){
		p->TaskState = TTS_DMT;
		p->Hdr.Id    = -1;

		//! 削除マークの付いたタスクをシステム管理タスク経由で削除する.
		wi_DeleteTaskReq( p->Hdr.Id );
	}
	wi_CommonUnlock();

	_endthreadex( 0 );
}

/****************************************************************************/
/*!
 *	@brief	タスクの強制終了.
 *
 *	@param	[in]	id		タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_TermTask( INT id )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! タスクIDのオブジェクトを取得する.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	//! スレッドを強制終了する.
	if( p->hThread ){
		TerminateThread( p->hThread, 0 );
	}
	p->TaskState = TTS_DMT;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	タスク優先度の変更.
 *
 *	@param	[in]	id			タスクID番号.
 *	@param	[in]	priority	タスク優先度.
 *
 *	@retval	エラーコード.
 */
ER		wi_ChangeTaskPriority( INT id, PRI priority )
{
	int			curpri,newpri;
	ER			ercd;
	WITSKOBJ	*p;

	//! タスクIDのオブジェクトを取得する.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	if( !p->hThread ){
		return E_OBJ;
	}
	//! 不正なタスク優先度の場合はエラーにする.
	if( priority == 0 ){
		return E_PAR;
	}
	p->TaskPri = priority;

	//! 現在のスレッドの相対優先順位値を取得する.
	curpri = GetThreadPriority( p->hThread );

	//! 変更するタスク優先度をスレッドの相対優先順位値に変換する.
	newpri = ConvertPriority( priority );

	//! スレッドの相対優先順位値が変更される場合、スレッドのプライオリティを変更する.
	if( curpri != newpri ){
		SetThreadPriority( p->hThread, newpri );
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	タスク優先度の参照.
 *
 *	@param	[in]	id			タスクID番号.
 *	@param	[in]	priority	現在のタスク優先度を格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_RefarenceTaskPriority( INT id, PRI *priority )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! タスクIDのオブジェクトを取得する.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	//! 引数が不正な場合はエラーにする.
	if( !priority ){
		return E_PAR;
	}
	//! タスクの優先度を戻り値にセットする.
	*priority = p->TaskPri;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	タスクの状態参照.
 *
 *	@param	[in]	id		タスクID番号.
 *	@param	[in]	sts		タスク状態を格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_RefarenceTask( INT id, WITSKSTAT *sts )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! タスクIDのオブジェクトを取得する.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	//! タスクの状態を構造体にセットする.
	sts->ExtInfo    = p->ExtInfo;
	sts->TaskPri    = p->TaskPri;
	sts->TaskState  = p->TaskState;
	sts->EventType  = p->EventType;
	sts->WaitId     = p->WaitId;
	sts->WakeupCnt  = p->WakeupCnt;
	sts->SuspendCnt = p->SuspendCnt;
	sts->TaskAtr    = p->TaskAtr;
	sts->TaskAdr    = p->TaskAdr;
	sts->InitPri    = p->InitPri;
	sts->StackSize  = p->StackSize;
	sts->ActiveCnt  = p->ActiveCnt;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	起床待ち.
 *
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		wi_SleepTask( TMO tmout )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! 自タスクのタスク･オブジェクトを取得する.
	p = FindTaskObject( TSK_SELF, &ercd );
	if( !p ){
		return E_OBJ;
	}
	if( !p->hThread ){
		return E_OBJ;
	}
	//! 起床要求カウンタが貯まっている場合はイベント待ちをしないで正常終了にする.
	if( p->WakeupCnt > 0 ){
		p->WakeupCnt--;
		return E_OK;
	}
	//! イベント待ちをする.
	return wi_TaskWait( p->Hdr.Id, TTW_SLP, tmout, 0, NULL );
}

/****************************************************************************/
/*!
 *	@brief	タスクの起床.
 *
 *	@param	[in]	id		タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_WakeupTask( INT id )
{
	ER ercd;

	//! 指定されたタスクに対してイベントを発行する.
	ercd = wi_TaskWakeup( id, TTW_SLP, NULL );

	//! 指定されたタスクがslp_tsk()でイベント待ちをしていない場合は起床要求カウンタを+1する.
	if( ercd == E_OACV ){
		WITSKOBJ *p = wi_GetTaskObject( id );
		if( p ){
			p->WakeupCnt++;
		}
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	タスクの起床要求を無効化.
 *
 *	@param	[in]	id			タスクID番号.
 *	@param	[in]	p_wupcnt	キューイングされていた起床要求回数を格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_CancelWakeup( INT id, INT *p_wupcnt )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! タスクIDのオブジェクトを取得する.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	if( !p->hThread ){
		return E_OBJ;
	}
	//! 起床要求回数を戻り値に格納する.
	if( p_wupcnt ){
		*p_wupcnt = p->WakeupCnt;
	}
	//! タスクの起床要求回数をクリアする.
	p->WakeupCnt = 0;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	待ち状態の強制解除.
 *
 *	@param	[in]	id		タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_ReleaseWait( INT id )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! 自タスクが指定された場合はエラーにする.
	if( id == TSK_SELF ){
		return E_OBJ;
	}
	//! タスクIDのオブジェクトを取得する.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	if( !p->hThread ){
		return E_OBJ;
	}
	//! イベント待ちをしていない場合はエラーにする.
	if( p->EventType == 0 ){
		return E_OBJ;
	}
	//! 待ち状態の強制解除フラグをセットしてイベントを発行する.
	p->RelRes = TRUE;
	if( !SetEvent( p->hEvent ) ){
		return E_SYS;
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	強制待ち状態への移行.
 *
 *	@param	[in]	id		タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_SuspendTask( INT id )
{
	DWORD		cnt;
	ER			ercd;
	WITSKOBJ	*p;

	//! タスクIDのオブジェクトを取得する.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	if( !p->hThread ){
		return E_OBJ;
	}
	//! スレッドの実行を中断する.
	cnt = SuspendThread( p->hThread );
	if( cnt == -1 ){
		return E_SYS;
	}
	p->TaskState = TTS_SUS;

	//! スレッドの中断カウンタを+1する.
	p->SuspendCnt = cnt + 1;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	強制待ち状態からの再開.
 *
 *	@param	[in]	id		タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_ResumeTask( INT id )
{
	DWORD		cnt;
	ER			ercd;
	WITSKOBJ	*p;

	//! タスクIDのオブジェクトを取得する.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	if( !p->hThread ){
		return E_OBJ;
	}
	//! スレッドの実行を再開する.
	cnt = ResumeThread( p->hThread );
	if( cnt == -1 ){
		return E_SYS;
	}
	//! スレッドが再開するときにステータスを「タスク実行中」に戻す.
	if( cnt == 1 ){
		if( p->EventType == 0 ){
			p->TaskState = TTS_RUN;
		}else{
			p->TaskState = TTS_WAI;
		}
	}
	//! スレッドが中断していなかった場合はエラーにする.
	if( cnt == 0 ){
		p->SuspendCnt = 0;
		return E_OBJ;
	}
	//! スレッドの中断カウンタを-1する.
	p->SuspendCnt = cnt - 1;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	強制待ち状態からの強制再開.
 *
 *	@param	[in]	id		タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_ForceResumeTask( INT id )
{
	DWORD		cnt;
	ER			ercd;
	WITSKOBJ	*p;

	//! タスクIDのオブジェクトを取得する.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	if( !p->hThread ){
		return E_OBJ;
	}
	//! スレッドのレジューム状態が解除されるまで繰り返す.
	do {
		cnt = ResumeThread( p->hThread );
	} while( cnt > 1 );

	if( cnt == -1 ){
		return E_SYS;
	}
	//! スレッドが再開するときにステータスを「タスク実行中」に戻す.
	if( p->EventType == 0 ){
		p->TaskState = TTS_RUN;
	}else{
		p->TaskState = TTS_WAI;
	}
	//! スレッドの中断カウンタをクリアする.
	p->SuspendCnt = 0;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	自タスクの遅延.
 *
 *	@param	[in]	dlytim	遅延時間.
 *
 *	@retval	エラーコード.
 */
ER		wi_DelayTask( TMO dlytim )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! 引数が不正な場合はエラーにする.
	if( dlytim == TMO_FEVR ){
		return E_PAR;
	}
	//! 自タスクのタスク･オブジェクトを取得する.
	p = FindTaskObject( TSK_SELF, &ercd );
	if( !p || !p->hThread ){
		return E_CTX;
	}
	//! イベント待ちでタイムアウトをさせる.
	ercd = wi_TaskWait( p->Hdr.Id, TTW_DLY, dlytim, 0, NULL );
	if( ercd == E_TMOUT ){
		ercd  = E_OK;
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	指定されたタスクIDのオブジェクトを取り出す.
 *
 *	@param	[in]	id		タスクID番号.
 *
 *	@retval	タスク･オブジェクト構造体のポインタ.
 */
WITSKOBJ	*wi_GetTaskObject( INT id )
{
	//! 自タスクのオブジェクトを取得する.
	if( id == TSK_SELF ){
		DWORD		tid = GetCurrentThreadId();
		WITSKOBJ	*p  = (WITSKOBJ *)ObjList;
		while( p ){
			if( p->ThreadId == tid ){
				return p;
			}
			p = (WITSKOBJ *)(p->Hdr.Next);
		}
		return NULL;
	}
	//! 指定されたタスクIDのオブジェクトを取得する.
	return (WITSKOBJ *)wi_GetObject( id, ObjList );
}

/****************************************************************************/
/*!
 *	@brief	指定されたタスクIDのオブジェクトを取り出す.
 *
 *	@param	[in]	id		タスクID番号.
 *	@param	[in]	ercd	エラーコードを格納する領域のポインタ.
 *
 *	@retval	タスク･オブジェクト構造体のポインタ.
 */
static WITSKOBJ	*FindTaskObject( INT id, ER *ercd )
{
	WITSKOBJ *p;

	//! タスクIDのオブジェクトを取得する.
	p = wi_GetTaskObject( id );
	if( !p ){
		*ercd = (id == TSK_SELF || id >= TMAX_MAXTSK) ? E_ID : E_NOEXS;
		return NULL;
	}
	*ercd = E_OK;
	return p;
}

/****************************************************************************/
/*!
 *	@brief	タスク優先度をWindowsスレッドの相対優先順位値に変更する.
 *
 *	@param	[in]	tskpri	タスク優先度.
 *
 *	@retval	スレッドの相対優先順位値.
 */
static int		ConvertPriority( PRI tskpri )
{
	if( tskpri < 10 ){
		return THREAD_PRIORITY_ABOVE_NORMAL;
	}else
	if( tskpri < 50 ){
		return THREAD_PRIORITY_NORMAL;
	}else
	if( tskpri < 100 ){
		return THREAD_PRIORITY_BELOW_NORMAL;
	}
	return THREAD_PRIORITY_LOWEST;
}

/****************************************************************************/
/*!
 *	@brief	自タスクのタスクIDを取得する.
 *
 *	@param	なし.
 *
 *	@retval	自タスクのタスクID.
 */
DWORD	wi_GetActiveTaskId( void )
{
	DWORD		tid = GetCurrentThreadId();
	WITSKOBJ	*p  = (WITSKOBJ *)ObjList;
	while( p ){
		if( p->ThreadId == tid ){
			return p->Hdr.Id;
		}
		p = (WITSKOBJ *)(p->Hdr.Next);
	}
	return 0;
}

/****************************************************************************/
/*!
 *	@brief	自タスクをイベント待ちにする.
 *
 *	@param	[in]	wid		待ちオブジェクトのID.
 *	@param	[in]	type	イベント種別.
 *	@param	[in]	tmout	タイムアウト設定.
 *	@param	[in]	pri		オブジェクトの属性.
 *	@param	[out]	que		待ち行列の先頭のタスク･オブジェクトのポインタのポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_TaskWait( INT wid, INT type, TMO tmout, ATR pri, WIHDR **que )
{
	DWORD		ret_code;
	ER			ercd;
	WITSKOBJ	*tsk;

	//! ポーリングの場合はタイムアウトで終了する.
	if( tmout == TMO_POL ){
		return E_TMOUT;
	}
	//! 自タスクのタスク･オブジェクトを取得する.
	tsk = FindTaskObject( TSK_SELF, &ercd );
	if( !tsk ){
		return E_CTX;
	}
	//! イベント･ハンドルを作成していない場合はエラーにする.
	if( !tsk->hEvent ){
		return E_NOEXS;
	}
	//! 他のオブジェクトがイベント待ちをしている場合は処理を終了にする.
	if( tsk->EventType != 0 ){
		return E_OACV;
	}
	//! イベント･ハンドルを「使用中」にする.
	tsk->EventType = type;
	tsk->WaitId    = wid;
	tsk->QueLink   = NULL;
	tsk->TaskState = TTS_WAI;

	//! タスクを待ち行列に追加する.
	if( que ){
		*que = wi_AddWaitTaskList( TSK_SELF, pri, *que );
	}
	//! ミューテックスを一旦解除する.
	wi_CommonUnlock();

	//! イベントの発生を待つ.
	ret_code = WaitForSingleObject( tsk->hEvent, wi_CvtTimeOutValue( tmout ) );

	//! 再度ミューテックスを掛ける.
	wi_CommonLock();

	//! タスクを待ち行列から削除する.
	if( que ){
		*que = wi_DelWaitTaskList( TSK_SELF, *que );
	}
	//! イベント･ハンドルを「未使用」に戻す.
	tsk->EventType = 0;
	tsk->WaitId    = 0;
	tsk->QueLink   = NULL;
	tsk->TaskState = TTS_RUN;

	switch( ret_code ){
	case WAIT_OBJECT_0:
		if( tsk->DelRes ){
			ercd = E_DLT;
		}else
		if( tsk->RelRes ){
			ercd = E_RLWAI;
		}else{
			ercd = E_OK;
		}
		break;

	case WAIT_TIMEOUT:
		ercd = E_TMOUT;
		break;

	default:
		ercd = E_SYS;
		break;
	}
	tsk->DelRes = FALSE;
	tsk->RelRes = FALSE;
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	イベント待ちしているタスクを起床させる.
 *
 *	@param	[in]	id		タスクID番号.
 *	@param	[in]	type	イベント種別.
 *	@param	[out]	que		待ち行列の先頭のタスク･オブジェクトのポインタのポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_TaskWakeup( INT id, INT type, WIHDR **que )
{
	ER			ercd;
	WITSKOBJ	*tsk;

	//! タスクIDのオブジェクトを取得する.
	tsk = FindTaskObject( id, &ercd );
	if( !tsk ){
		return ercd;
	}
	//! イベント･ハンドルを作成していない場合はエラーにする.
	if( !tsk->hEvent ){
		return E_NOEXS;
	}
	//! イベント待ちをしていない場合はエラーにする.
	if( tsk->EventType == 0 ){
		return E_OACV;
	}
	//! タスクが休止中の場合はエラーにする.
	if( tsk->TaskState == TTS_DMT ){
		return E_OBJ;
	}
	//! 他のオブジェクトがイベント待ちをしている場合はエラーにする.
	if( tsk->EventType != type ){
		return E_OACV;
	}
	//! イベントを発行する.
	if( !SetEvent( tsk->hEvent ) ){
		return E_SYS;
	}
	//! 起床したタスクを待ち行列から削除する.
	if( que ){
		*que = wi_DelWaitTaskList( id, *que );
	}
	//! イベント･ハンドルを「未使用」に戻す.
	tsk->EventType = 0;
	tsk->WaitId    = 0;
	tsk->QueLink   = NULL;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	待ち行列にタスクを追加する.
 *
 *	@param	[in]	id		タスクID番号.
 *	@param	[in]	pri		オブジェクトの属性.
 *	@param	[in]	que		待ち行列の先頭のタスク･オブジェクトのポインタ.
 *
 *	@retval	待ち行列の先頭のタスク･オブジェクトのポインタ.
 */
WIHDR	*wi_AddWaitTaskList( INT id, ATR pri, WIHDR *que )
{
	ER			ercd;
	WITSKOBJ	*add_tsk,*que_tsk;

	//! 指定されたタスクのタスク･オブジェクトを取得する.
	add_tsk = FindTaskObject( id, &ercd );
	if( !add_tsk ){
		return que;
	}
	//! 待ち行列にタスクがない場合は、このタスクを待ち行列の先頭にする.
	if( !que ){
		return (WIHDR *)add_tsk;
	}
	if( pri & TA_TPRI ){
		/*!
		 * 待ち行列の先頭タスクより指定されたタスクの方が優先度が高い場合は
		 * 指定されたタスクを待ち行列の先頭にする.
		 */
		que_tsk = (WITSKOBJ *)que;
		if( que_tsk->TaskPri > add_tsk->TaskPri ){
			add_tsk->QueLink = que_tsk;
			return (WIHDR *)add_tsk;
		}
		/*!
		 * 待ち行列中のタスクの優先度より指定されたタスクの優先度が高くなったところに
		 * 指定されたタスクを挿入する.
		 */
		while( que_tsk->QueLink ){
			if( que_tsk->QueLink->TaskPri > add_tsk->TaskPri ){
				add_tsk->QueLink = que_tsk->QueLink;
				break;
			}
			que_tsk = que_tsk->QueLink;
		}
		que_tsk->QueLink = add_tsk;
	}else{
		//! FIFO順の場合、待ち行列の最後にタスクを追加する.
		que_tsk = (WITSKOBJ *)que;
		while( que_tsk->QueLink ){
			que_tsk = que_tsk->QueLink;
		}
		que_tsk->QueLink = add_tsk;
	}
	return que;
}

/****************************************************************************/
/*!
 *	@brief	待ち行列からタスクを削除する.
 *
 *	@param	[in]	id		タスクID番号.
 *	@param	[in]	que		待ち行列の先頭のタスク･オブジェクトのポインタ.
 *
 *	@retval	待ち行列の先頭のタスク･オブジェクトのポインタ.
 */
WIHDR	*wi_DelWaitTaskList( INT id, WIHDR *que )
{
	ER			ercd;
	WITSKOBJ	*del_tsk,*que_tsk;

	//! 待ち行列にタスクがない場合処理しない.
	if( !que ){
		return NULL;
	}
	//! タスク･オブジェクトを取得する.
	del_tsk = FindTaskObject( id, &ercd );
	if( !del_tsk ){
		return que;
	}
	/*!
	 * 待ち行列の先頭が指定されたタスクの場合は待ち行列の先頭タスクを削除する.
	 * (戻り値は次のタスク･オブジェクトのポインタとなる.)
	 */
	que_tsk = (WITSKOBJ *)que;
	if( que_tsk->Hdr.Id == del_tsk->Hdr.Id ){
		WIHDR *wk        = (WIHDR *)del_tsk->QueLink;
		del_tsk->QueLink = NULL;
		return wk;
	}
	/*!
	 * 待ち行列から指定されたタスクを削除する.
	 * (待ち行列の先頭のタスクは変わらない.)
	 */
	while( que_tsk->QueLink ){
		if( que_tsk->QueLink->Hdr.Id == del_tsk->Hdr.Id ){
			que_tsk->QueLink = del_tsk->QueLink;
			del_tsk->QueLink = NULL;
			break;
		}
		que_tsk = que_tsk->QueLink;
	}
	return que;
}

/****************************************************************************/
/*!
 *	@brief	待ち行列の先頭のタスクのID番号を取得する.
 *
 *	@param	[in]	que		待ち行列の先頭のタスク･オブジェクトのポインタ.
 *
 *	@retval	待ち行列の先頭のタスクのID番号.
 */
DWORD	wi_GetWaitTaskListFirstId( WIHDR *que )
{
	//! 待ち行列にタスクがない場合処理しない.
	if( !que ){
		return 0;
	}
	//! 待ち行列の先頭のタスクのタスクID番号を返す.
	return que->Id;
}

/****************************************************************************/
/*!
 *	@brief	リソースが削除されるときに待ち行列にあるタスクを解放する.
 *
 *	@param	[in]	que		待ち行列の先頭のタスク･オブジェクトのポインタ.
 *
 *	@retval	なし.
 */
void	wi_WakeupDelResource( WIHDR *que )
{
	WITSKOBJ *p;

	p = (WITSKOBJ *)que;
	while( p ){
		//! イベント･ハンドルを「未使用」に戻す.
		p->EventType = 0;
		p->WaitId    = 0;
		if( p->hThread && p->hEvent ){
			//! リソースが削除されることを示すフラグをセットしてイベントを発行する.
			p->DelRes = TRUE;
			SetEvent( p->hEvent );
		}
		//! 待ち行列から次のタスク･オブジェクトを取り出す.
		p = p->QueLink;

		//! 待ちキューからタスクを削除する.
		p->QueLink = NULL;
	}
}

/* End of file */
