/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_task.h
 *
 *	@brief	Windows版 iTRONサービスコール (タスク機能).
 *
 *	@author	金澤 宣明
 */
#ifndef	__WI_TASK_H__
#define	__WI_TASK_H__

#include "wi_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 * 構造体定義.
 *
 ****************************************************************************/
/*!
 *
 * @brief タスク･オブジェクト構造体.
 *
 */
typedef struct _WITSKOBJ {
	WIHDR				Hdr;			//!< オブジェクト･ヘッダ.
	struct _WITSKOBJ	*QueLink;		//!< 待ち行列へのリンク用ポインタ.
	HANDLE				hThread;		//!< スレッド･ハンドル.
	HANDLE				hEvent;			//!< イベント･ハンドル.
	INT					EventType;		//!< イベント種別.
	UINT				TaskState;		//!< タスク状態.
	unsigned int		ThreadId;		//!< スレッドID番号.
	ATR					TaskAtr;		//!< タスク属性.
	FP					TaskAdr;		//!< タスク起動アドレス.
	PRI					TaskPri;		//!< タスク優先度.
	PRI					InitPri;		//!< タスク起動時の初期優先度.
	INT					StackSize;		//!< スタックサイズ.
	VP					ExtInfo;		//!< 拡張情報.
	DWORD				StartCode;		//!< タスク起動コード.
	INT					SuspendCnt;		//!< タスクが中断した回数.
	INT					WakeupCnt;		//!< タスクの起床要求回数.
	INT					ActiveCnt;		//!< タスクの起動要求回数.
	ID					WaitId;			//!< 待ちオブジェクトのID.
	VP					Param[5];		//!< 同期処理用の作業領域.
	BOOL				DelRes;			//!< TRUE = リソース削除によるタスクの起床.
	BOOL				RelRes;			//!< TRUE = 待ち状態の強制解除によるタスクの起床.
} WITSKOBJ;

/*!
 *
 * @brief タスクの状態参照用構造体.
 *
 */
typedef struct {
	ATR					TaskAtr;		//!< タスク属性.
	FP					TaskAdr;		//!< タスク起動アドレス.
	UINT				TaskState;		//!< タスク状態.
	PRI					TaskPri;		//!< タスク優先度.
	PRI					InitPri;		//!< タスク起動時の初期優先度.
	ID					WaitId;			//!< 待ちオブジェクトのID.
	INT					EventType;		//!< イベント種別.
	INT					SuspendCnt;		//!< タスクが中断した回数.
	INT					WakeupCnt;		//!< タスクの起床要求回数.
	INT					ActiveCnt;		//!< タスクの起動要求回数.
	INT					StackSize;		//!< スタックサイズ.
	VP					ExtInfo;		//!< 拡張情報.
} WITSKSTAT;

/****************************************************************************
 *
 * 関数定義.
 *
 ****************************************************************************/
void		wi_InitTask( void );
void		wi_QuitTask( void );
ER			wi_CreateTask( INT id, const WITSKOBJ *obj );
ER			wi_DeleteTask( INT id );
ER			wi_StartTask( INT id, DWORD start_code, BOOL exist_stcd );
int			wi_CancelStartReq( INT id );
void		wi_ExitTask( void );
void		wi_ExpendTask( void );
ER			wi_TermTask( INT id );
ER			wi_ChangeTaskPriority( INT id, PRI priority );
ER			wi_RefarenceTaskPriority( INT id, PRI *priority );
ER			wi_RefarenceTask( INT id, WITSKSTAT *sts );
ER			wi_SleepTask( TMO tmout );
ER			wi_WakeupTask( INT id );
ER			wi_CancelWakeup( INT id, INT *p_wupcnt );
ER			wi_ReleaseWait( INT id );
ER			wi_SuspendTask( INT id );
ER			wi_ResumeTask( INT id );
ER			wi_ForceResumeTask( INT id );
ER			wi_DelayTask( TMO dlytim );
WITSKOBJ	*wi_GetTaskObject( INT id );
DWORD		wi_GetActiveTaskId( void );
ER			wi_TaskWait( INT wid, INT type, TMO tmout, ATR pri, WIHDR **que );
ER			wi_TaskWakeup( INT id, INT type, WIHDR **que );
WIHDR		*wi_AddWaitTaskList( INT id, ATR pri, WIHDR *que );
WIHDR		*wi_DelWaitTaskList( INT id, WIHDR *que );
DWORD		wi_GetWaitTaskListFirstId( WIHDR *que );
void		wi_WakeupDelResource( WIHDR *que );

#ifdef __cplusplus
}
#endif
#endif	// __WI_TASK_H__
/* End of file */
