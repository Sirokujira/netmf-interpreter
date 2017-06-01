/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_interrupt.c
 *
 *	@brief	Windows版 iTRONサービスコール (割り込み機能).
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include <process.h>
#include "wi_interrupt.h"

/****************************************************************************
 *
 * 割り込みスレッドへのメッセージ.
 *
 ****************************************************************************/
#define	WM_SYSTEM_EXIT	(WM_USER + 1)		//!< システムの終了.
#define	WM_INTRRUPT_REQ	(WM_USER + 2)		//!< 割り込み要求.

/****************************************************************************
 *
 * ローカル関数定義.
 *
 ****************************************************************************/
static unsigned int __stdcall	IntrTask( void* arg );
static void			CallIntrruptHandler( INT no );

/****************************************************************************
 *
 * ローカル変数定義.
 *
 ****************************************************************************/
static WIHDR		*ObjList;			//!< 割り込みハンドラ･リストのポインタ.
static HANDLE		IntrThread;			//!< 割り込みスレッドのハンドル.
static DWORD		IntrTid;			//!< 割り込みスレッドの識別子.
static BOOL			CpuLockFlg;			//!< TRUE = CPUロック中.

/****************************************************************************/
/*!
 *	@brief	割り込み機能の初期処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_InitInterrupt( void )
{
	unsigned int tid;

	ObjList    = NULL;
	IntrThread = NULL;
	IntrTid    = 0;
	CpuLockFlg = FALSE;

	//! 割り込みスレッドを起動する.
	IntrThread = (HANDLE)_beginthreadex( NULL, 0, &IntrTask, NULL, 0, &tid );

	//! タスクの優先度を設定する.
	SetThreadPriority( IntrThread, THREAD_PRIORITY_HIGHEST );

}

/****************************************************************************/
/*!
 *	@brief	割り込み機能の終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_QuitInterrupt( void )
{
	WIHDR		*next_ptr;
	WIINTOBJ	*p;

	//! システム管理スレッドを終了させる.
	if( IntrThread ){
		//! 割り込みスレッドに終了を通知する.
		PostThreadMessage( IntrTid, WM_SYSTEM_EXIT, 0, 0 );

		//! - スレッドが停止するのを確認する.
		wi_DormantThread( IntrThread, 1000 );

		//! - 割り込みスレッドのハンドルを解放する.
		CloseHandle( IntrThread );
	}
	p = (WIINTOBJ *)ObjList;
	while( p ){
		next_ptr = p->Hdr.Next;

		//! 割り込みハンドラ構造体を解放する.
		SAFE_RELEASE( p );

		//! 次の割り込みハンドラ構造体を取り出す.
		p = (WIINTOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	割り込みハンドラの定義.
 *
 *	@param	[in]	no		割り込みハンドラ番号.
 *	@param	[in]	obj		割り込みハンドラ.オブジェクト構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_DefineIntrruptHander( INT no, const WIINTOBJ *obj )
{
	ER			ercd;
	WIINTOBJ	*p;

	//! 既に生成しているハンドラ番号の場合はエントリアドレスを更新する.
	p = (WIINTOBJ *)wi_GetObject( no, ObjList );
	if( p ){
		p->IntrAdr = obj->IntrAdr;
		p->Enabled = FALSE;
		p->IntrCnt = 0;
		return E_OK;
	}
	//! 割り込みハンドラ･オブジェクトを作成する.
	p = (WIINTOBJ *)wi_CreateObject( no, TMAX_MAXINT, sizeof(WIINTOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストに割り込みハンドラを追加する.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	割り込みの禁止.
 *
 *	@param	[in]	no		割り込みハンドラ番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_DisableIntrrupt( INT no )
{
	ER			ercd;
	WIINTOBJ	*p;

	//! ハンドラ番号のオブジェクトを取得する.
	p = (WIINTOBJ *)wi_FindObject( no, TMAX_MAXINT, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 割り込みを禁止する.
	p->Enabled = FALSE;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	割り込みの許可.
 *
 *	@param	[in]	no		割り込みハンドラ番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_EnableIntrrupt( INT no )
{
	ER			ercd;
	WIINTOBJ	*p;

	//! ハンドラ番号のオブジェクトを取得する.
	p = (WIINTOBJ *)wi_FindObject( no, TMAX_MAXINT, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 割り込みを許可する.
	p->Enabled = TRUE;

	//! 割り込みが保留されていた場合は割り込みを発生させる.
	if( p->IntrCnt > 0 ){
		wi_IntrruptRequest( no );
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	CPUロック状態への移行.
 *
 *	@param	なし.
 *
 *	@retval	エラーコード.
 */
ER		wi_LockCPU( void )
{
	//! CPUロックフラグをセットする.
	CpuLockFlg = TRUE;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	CPUロック状態の解除.
 *
 *	@param	なし.
 *
 *	@retval	エラーコード.
 */
ER		wi_UnLockCPU( void )
{
	//! CPUロックフラグを解除する.
	CpuLockFlg = FALSE;

	//! 保留されていた割り込みハンドラの呼び出しを行う.
	wi_DelayedIntrrupt();

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	CPUロック状態の参照.
 *
 *	@param	なし.
 *
 *	@retval	TRUE = CPUロック中. / FALSE = CPU非ロック中.
 */
BOOL	wi_IsCPULock( void )
{
	return CpuLockFlg;
}

/****************************************************************************/
/*!
 *	@brief	保留されていた割り込みハンドラの呼び出しを行う.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_DelayedIntrrupt( void )
{
	WIINTOBJ *p = (WIINTOBJ *)ObjList;
	while( p ){
		//! 割り込みが保留されていた場合は割り込みを発生させる.
		if( p->IntrCnt > 0 ){
			wi_IntrruptRequest( p->Hdr.Id );
		}
		p = (WIINTOBJ *)p->Hdr.Next;
	}
}

/****************************************************************************/
/*!
 *	@brief	割り込みを発生させる.
 *
 *	@param	[in]	no		割り込みハンドラ番号.
 *
 *	@retval	なし.
 */
void	wi_IntrruptRequest( INT no )
{
	if( IntrTid ){
		PostThreadMessage( IntrTid, WM_INTRRUPT_REQ, (WPARAM)no, 0 );
	}
}

/****************************************************************************/
/*!
 *	@brief	割り込み要求をクリアする.
 *
 *	@param	[in]	no		割り込みハンドラ番号.
 *
 *	@retval	なし.
 */
void	wi_ClearIntrruptRequest( INT no )
{
	ER			ercd;
	WIINTOBJ	*p;

	//! ハンドラ番号のオブジェクトを取得する.
	p = (WIINTOBJ *)wi_FindObject( no, TMAX_MAXINT, ObjList, &ercd );
	if( p ){
		//! 割り込み要求をクリアする.
		p->IntrCnt = 0;
	}
}

/****************************************************************************/
/*!
 *	@brief	割り込みタスク.
 *
 *	@param	[in]	arg		タスクリソース構造体のポインタ.
 *
 *	@retval	常に0を返す.
 */
static unsigned __stdcall IntrTask( void* arg )
{
	MSG	msg;

	//! スレッド識別子を取得する.
	IntrTid = GetCurrentThreadId();

	//! メッセージループ.
	while( GetMessage( &msg, NULL, 0, 0 ) ){

		//! システムの終了の場合はメッセージループを抜ける.
		if( msg.message == WM_SYSTEM_EXIT ){
			break;
		}
		switch( msg.message ){
		case WM_INTRRUPT_REQ:
			CallIntrruptHandler( (INT)msg.wParam );
			break;
		}
	}
	_endthreadex( 0 );
	return 0;
}

/****************************************************************************/
/*!
 *	@brief	割り込みハンドラを呼び出す.
 *
 *	@param	[in]	no		割り込みハンドラ番号.
 *
 *	@retval	なし.
 */
static void		CallIntrruptHandler( INT no )
{
	wi_CommonLock();
	do {
		FP			intr_adr;
		ER			ercd;
		WIINTOBJ	*p;

		//! 割り込みハンドラ構造体を取り出す.
		p = (WIINTOBJ *)wi_FindObject( no, TMAX_MAXINT, ObjList, &ercd );
		if( !p ){
			break;
		}
		//! 割り込みエントリ･アドレスがない場合は呼び出さない.
		if( !p->IntrAdr ){
			break;
		}
		//! 割り込み禁止の場合は呼び出さない.
		if( !p->Enabled || wi_IsCPULock() ){
			p->IntrCnt++;
			break;
		}
		p->IntrCnt = 0;

		intr_adr = p->IntrAdr;

		wi_CommonUnlock();

		//! 割り込みハンドラを呼び出す.
		intr_adr();
		return;

	} while( FALSE );

	wi_CommonUnlock();
}

/* End of file */
