/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_mutex.h
 *
 *	@brief	Windows版 iTRONサービスコール (ミューテックス).
 *
 *	@author	金澤 宣明
 */
#ifndef	__WI_MUTEX_H__
#define	__WI_MUTEX_H__

#include "wi_common.h"
#include "wi_task.h"

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
 * @brief ミューテックス･オブジェクト構造体.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< オブジェクト･ヘッダ.
	ATR			Attribute;		//!< ミューテックス属性.
	PRI			CeilPri;		//!< ミューテックスの上限優先度.
	INT			LockId;			//!< ミューテックスをロックしているタスクのID番号.
	WIHDR		*WaitQue;		//!< セマフォ獲得待ちの待ち行列のポインタ.
} WIMTXOBJ;

/*!
 *
 * @brief ミューテックスの状態参照用構造体.
 *
 */
typedef struct {
	INT			LockId;			//!< ミューテックスをロックしているタスクのID番号.
	INT			WaitId;			//!< ミューテックス待ち行列の先頭のタスクID番号.
} WIMTXSTAT;

/****************************************************************************
 *
 * 関数定義.
 *
 ****************************************************************************/
void	wi_InitMutex( void );
void	wi_QuitMutex( void );
ER		wi_CreateMutex( INT id, const WIMTXOBJ *obj );
ER		wi_DeleteMutex( INT id );
ER		wi_LockMutex( INT id, TMO tmout );
ER		wi_UnlockMutex( INT id );
ER		wi_RefarenceMutex( INT id, WIMTXSTAT *sts );
void	wi_AllReleaseMutex( INT id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_MUTEX_H__
/* End of file */
