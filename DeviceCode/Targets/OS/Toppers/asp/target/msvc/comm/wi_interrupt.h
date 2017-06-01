/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_interrupt.h
 *
 *	@brief	Windows版 iTRONサービスコール (割り込み機能).
 *
 *	@author	金澤 宣明
 */
#ifndef	__WI_INTERRUPT_H__
#define	__WI_INTERRUPT_H__

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
 * @brief 割り込みハンドラ･オブジェクト構造体.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< オブジェクト･ヘッダ.
	ATR			Attribute; 		//!< 割り込みハンドラ属性.
	FP			IntrAdr;		//!< 割り込みハンドラのアドレス.
	BOOL		Enabled;		//!< TRUE = 割り込み許可.
	UINT		IntrCnt;		//!< 割り込みを保留した回数.
} WIINTOBJ;

/****************************************************************************
 *
 * 関数定義.
 *
 ****************************************************************************/
void	wi_InitInterrupt( void );
void	wi_QuitInterrupt( void );
ER		wi_DefineIntrruptHander( INT no, const WIINTOBJ *obj );
ER		wi_DisableIntrrupt( INT no );
ER		wi_EnableIntrrupt( INT no );
ER		wi_LockCPU( void );
ER		wi_UnLockCPU( void );
BOOL	wi_IsCPULock( void );
void	wi_DelayedIntrrupt( void );
void	wi_IntrruptRequest( INT no );
void	wi_ClearIntrruptRequest( INT no );

#ifdef __cplusplus
}
#endif
#endif	// __WI_INTERRUPT_H__
/* End of file */
