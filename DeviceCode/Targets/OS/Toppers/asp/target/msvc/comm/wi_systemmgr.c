/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_systemmgr.c
 *
 *	@brief	Windows版 iTRONサービスコール (システム状態管理機能).
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_systemmgr.h"

static BOOL	DisEnabled = TRUE;;

/****************************************************************************/
/*!
 *	@brief	システム状態管理機能の初期処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_InitSysMgr( void )
{
}

/****************************************************************************/
/*!
 *	@brief	システム状態管理機能の終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_QuitSysMgr( void )
{
}

/****************************************************************************/
/*!
 *	@brief	タスクの優先順位の回転.
 *
 *	@param	[in]	tskpri	優先順位を回転する優先度.
 *
 *	@retval	エラーコード.
 */
ER		wi_RotateTaskPriority( PRI tskpri )
{
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	実行状態のタスクIDの参照.
 *
 *	@param	[out]	p_tskid		タスクID番号を格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_GetTid( ID *p_tskid )
{
	//! 引数が不正な場合はエラーにする.
	if( !p_tskid ){
		return E_PAR;
	}
	//! 本サービスコールを行ったタスクのIDを返す.
	*p_tskid = wi_GetTaskId();

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	ディスパッチの禁止.
 *
 *	@param	なし.
 *
 *	@retval	エラーコード.
 */
ER		wi_DisabledDispatch( void )
{
	DisEnabled = FALSE;
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	ディスパッチの許可.
 *
 *	@param	なし.
 *
 *	@retval	エラーコード.
 */
ER		wi_EnabledDispatch( void )
{
	DisEnabled = TRUE;
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	システム状態の参照.
 *
 *	@param	[out]	pk_rsys		システム状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_GetSystemInfo( T_RSYS *pk_rsys )
{
	//! 引数が不正な場合はエラーにする.
	if( !pk_rsys ){
		return E_PAR;
	}
	//! 構造体をクリアする.
	memset( pk_rsys, 0, sizeof(T_RSYS) );

	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	バージョン情報の参照.
 *
 *	@param	[out]	pk_ver		バージョン情報を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
#ifdef __WIN_ITRON3_H__
ER		wi_GetVersion( T_VER *pk_ver )
{
	//! 引数が不正な場合はエラーにする.
	if( !pk_ver ){
		return E_PAR;
	}
	//! 構造体をクリアする.
	memset( pk_ver, 0, sizeof(T_VER) );

	return E_NOSPT;
}
#else
ER		wi_GetVersion( T_RVER *pk_ver )
{
	//! 引数が不正な場合はエラーにする.
	if( !pk_ver ){
		return E_PAR;
	}
	//! 構造体をクリアする.
	memset( pk_ver, 0, sizeof(T_RVER) );

	return E_NOSPT;
}
#endif

/****************************************************************************/
/*!
 *	@brief	コンフィグレーション情報の参照.
 *
 *	@param	[out]	pk_rcfg		コンフィグレーション情報を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_GetConfigInfo( T_RCFG *pk_rcfg )
{
	//! 引数が不正な場合はエラーにする.
	if( !pk_rcfg ){
		return E_PAR;
	}
	//! 構造体をクリアする.
	memset( pk_rcfg, 0, sizeof(T_RCFG) );

	return E_NOSPT;
}

/* End of file */
