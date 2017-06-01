/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_rendezvous_port.h
 *
 *	@brief	Windows版 iTRONサービスコール (ランデブ).
 *
 *	@author	金澤 宣明
 */
#ifndef	__WI_RENDEZVOUS_PORT_H__
#define	__WI_RENDEZVOUS_PORT_H__

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
 * @brief ランデブポート･オブジェクト構造体.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< オブジェクト･ヘッダ.
	ATR			Attribute;		//!< ランデブポート属性.
	INT			MaxCalMsg;		//!< 呼出時のメッセージの最大長.
	INT			MaxRepMsg;		//!< 返答時のメッセージの最大長.
	WIHDR		*CalWaitQue;	//!< ランデブ呼出待ちタスクの待ち行列のポインタ.
	WIHDR		*AcpWaitQue;	//!< ランデブ受付待ちタスクの待ち行列のポインタ.
	VP			ExtInfo;		//!< 拡張情報.
} WIPOROBJ;

/*!
 *
 * @brief ランデブポート状態の参照用構造体.
 *
 */
typedef struct {
	INT			CalWaitId;		//!< ランデブ呼出待ちタスクの待ち行列の先頭のタスクのID番号.
	INT			AcpWaitId;		//!< ランデブ受付待ちタスクの待ち行列の先頭のタスクのID番号.
	VP			ExtInfo;		//!< 拡張情報.
} WIPORSTAT;

/*!
 *
 * @brief ランデブ･オブジェクト構造体.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< オブジェクト･ヘッダ.
	INT			TaskId;			//!< ランデブ終了待ちをしているタスクID番号.
	INT			MaxRepMsg;		//!< 返答時のメッセージの最大長.
} WIRDVOBJ;

/*!
 *
 * @brief ランデブ状態の参照用構造体.
 *
 */
typedef struct {
	DWORD		WaitId;			//!< ランデブ終了待ちタスクのID番号.
} WIRDVSTAT;

/****************************************************************************
 *
 * 関数定義.
 *
 ****************************************************************************/
void	wi_InitRendPort( void );
void	wi_QuitRendPort( void );
ER		wi_CreateRendPort( INT id, const WIPOROBJ *pk_cpor );
ER		wi_DeleteRendPort( INT id );
ER		wi_CallRendPort( INT id, UINT ptn, VP msg, INT csize, INT *rsize, TMO tmout );
ER		wi_AcceptRendPort( INT id, UINT ptn, INT *no, VP msg, INT *size, TMO tmout );
ER		wi_FowardRendPort( INT id, UINT ptn, INT no, VP msg, INT cmsgsz );
ER		wi_ReplayRendPort( INT no, VP msg, INT size );
ER		wi_RefarenceRendPort( INT id, WIPORSTAT *sts );
ER		wi_RefarenceRendStat( INT no, WIRDVSTAT *sts );
void	wi_AllReleaseRendPort( INT id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_RENDEZVOUS_PORT_H__
/* End of file */
