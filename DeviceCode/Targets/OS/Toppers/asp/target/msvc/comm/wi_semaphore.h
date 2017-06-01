/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_semaphore.h
 *
 *	@brief	Windows版 iTRONサービスコール (セマフォ).
 *
 *	@author	金澤 宣明
 */
#ifndef	__WI_SEMAPHORE_H__
#define	__WI_SEMAPHORE_H__

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
 * @brief セマフォ･オブジェクト構造体.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< オブジェクト･ヘッダ.
	ATR			Attribute;		//!< セマフォ属性.
	INT			SemCnt;			//!< 現在のセマフォ･カウント.
	INT			MaxCnt;			//!< セマフォ･カウントの最大数.
	VP			ExtInfo;		//!< 拡張情報.
	WIHDR		*WaitQue;		//!< セマフォ獲得待ちの待ち行列のポインタ.
} WISEMOBJ;

/*!
 *
 * @brief セマフォの状態参照用構造体.
 *
 */
typedef struct {
	INT			WaitId;			//!< セマフォ待ち行列の先頭のタスクのID番号.
	INT			SemCnt;			//!< 現在のセマフォカウント値.
	VP			ExtInfo;		//!< 拡張情報.
} WISEMSTAT;

/****************************************************************************
 *
 * 関数定義.
 *
 ****************************************************************************/
void	wi_InitSemaphore( void );
void	wi_QuitSemaphore( void );
ER		wi_CreateSemaphore( INT id, const WISEMOBJ *obj );
ER		wi_DeleteSemaphore( INT id );
ER		wi_SignalSemaphore( INT id );
ER		wi_WaitSemaphore( INT id, TMO tmout );
ER		wi_RefarenceSemaphore( INT id, WISEMSTAT *sts );
void	wi_AllReleaseSemaphore( INT id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_SEMAPHORE_H__
/* End of file */
