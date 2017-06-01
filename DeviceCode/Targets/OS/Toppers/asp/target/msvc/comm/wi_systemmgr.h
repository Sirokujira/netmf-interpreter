/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_systemmgr.h
 *
 *	@brief	Windows版 iTRONサービスコール (システム状態管理機能).
 *
 *	@author	金澤 宣明
 */
#ifndef	__WI_SYSTEMMGR_H__
#define	__WI_SYSTEMMGR_H__

#include "wi_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 * 関数定義.
 *
 ****************************************************************************/
void	wi_InitSysMgr( void );
void	wi_QuitSysMgr( void );
ER		wi_RotateTaskPriority( PRI tskpri );
ER		wi_GetTid( ID *p_tskid );
ER		wi_DisabledDispatch( void );
ER		wi_EnabledDispatch( void );
ER		wi_GetSystemInfo( T_RSYS *pk_rsys );
ER		wi_GetConfigInfo( T_RCFG *pk_rcfg );
#ifdef __WIN_ITRON3_H__
ER		wi_GetVersion( T_VER *pk_ver );
#else
ER		wi_GetVersion( T_RVER *pk_ver );
#endif

#ifdef __cplusplus
}
#endif
#endif	// __WI_SYSTEMMGR_H__
/* End of file */
