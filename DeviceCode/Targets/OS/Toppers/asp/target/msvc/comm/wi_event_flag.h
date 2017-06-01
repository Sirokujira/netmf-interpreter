/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_event_flag.h
 *
 *	@brief	Windows版 iTRONサービスコール (イベントフラグ).
 *
 *	@author	金澤 宣明
 */
#ifndef	__WI_EVENT_FLAG_H__
#define	__WI_EVENT_FLAG_H__

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
 * @brief イベントフラグ･オブジェクト構造体.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< オブジェクト･ヘッダ.
	ATR			Attribute;		//!< イベントフラグ属性.
	UINT		FlgVal;			//!< イベントフラグのビットパターン.
	VP			ExtInfo;		//!< 拡張情報.
	WIHDR		*WaitQue;		//!< タスクの待ち行列のポインタ.
} WIFLGOBJ;

/*!
 *
 * @brief イベントフラグの状態参照用構造体.
 *
 */
typedef struct {
	UINT		FlgVal;			//!< イベントフラグのビットパターン.
	INT			WaitId;			//!< イベントフラグ待ち行列の先頭のタスクのID番号.
	VP			ExtInfo;		//!< 拡張情報.
} WIFLGSTAT;

/****************************************************************************
 *
 * 関数定義.
 *
 ****************************************************************************/
void	wi_InitEvFlag( void );
void	wi_QuitEvFlag( void );
ER		wi_CreateEvFlag( INT id, WIFLGOBJ *obj );
ER		wi_DeleteEvFlag( INT id );
ER		wi_SetEvFlag( INT id, UINT setptn );
ER		wi_ClearEvFlag( INT id, UINT clrptn );
ER		wi_WaitEvFlag( INT id, UINT *p_flgptn, UINT waiptn, UINT wfmode, TMO tmout );
ER		wi_RefarenceEvFlag( INT id, WIFLGSTAT *sts );
void	wi_AllReleaseEvFlag( INT id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_EVENT_FLAG_H__
/* End of file */
