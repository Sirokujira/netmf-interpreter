/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_mail_box.h
 *
 *	@brief	Windows版 iTRON(Ver3.0)サービスコール (メールボックス).
 *
 *	@author	金澤 宣明
 */
#ifndef	__WI_MAIL_BOX_H__
#define	__WI_MAIL_BOX_H__

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
 * @brief メールボックス･オブジェクト構造体.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< オブジェクト･ヘッダ.
	ATR			Attribute;		//!< メールボックス属性.
	PRI			MaxPriority;	//!< 送信されるメッセージ優先度の最大値.
	VP			ExtInfo;		//!< 拡張情報.
	T_MSG		*MsgQue;		//!< メッセージ･パケット･リストのポインタ.
	WIHDR		*WaitQue;		//!< タスクの待ち行列のポインタ.
} WIMBXOBJ;

/*!
 *
 * @brief メールボックスの状態参照用構造体.
 *
 */
typedef struct {
	INT			WaitId;			//!< メッセージ待ち行列の先頭のタスクのID番号.
	T_MSG		*NextMsg;		//!< 次に受信されるメッセージ.
	VP			ExtInfo;		//!< 拡張情報.
} WIMBXSTAT;

/****************************************************************************
 *
 * 関数定義.
 *
 ****************************************************************************/
void	wi_InitMailBox( void );
void	wi_QuitMailBox( void );
ER		wi_CreateMailBox( INT id, const WIMBXOBJ *obj );
ER		wi_DeleteMailBox( INT id );
ER		wi_SendMailBox( INT id, T_MSG *msg );
ER		wi_ReceiveMailBox( INT id, T_MSG **msg, TMO tmout );
ER		wi_RefarenceMailBox( INT id, WIMBXSTAT *sts );
void	wi_AllReleaseMailBox( INT id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_MAIL_BOX_H__
/* End of file */
