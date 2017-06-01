/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_message_buffer.h
 *
 *	@brief	Windows版 iTRONサービスコール (メッセージバッファ).
 *
 *	@author	金澤 宣明
 */
#ifndef	__WI_MESSAGE_BUFFER_H__
#define	__WI_MESSAGE_BUFFER_H__

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
 * @brief メッセージバッファ･オブジェクト構造体.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< オブジェクト･ヘッダ.
	ATR			SndAttr;		//!< メッセージバッファ属性 (メッセージ送信側).
	ATR			RcvAttr;		//!< メッセージバッファ属性 (メッセージ受信側).
	UINT		MaxMsg; 		//!< メッセージの最大長.
	UINT		MsgSize;		//!< メッセージバッファ領域のサイズ.
	BYTE		*MsgBuf;		//!< メッセージバッファ領域の先頭アドレス.
	UINT		GetPos;			//!< メールの読み出し位置.
	UINT		PutPos;			//!< メールの書き出し位置.
	WIHDR		*SndWaitQue;	//!< タスクの送信待ち行列のポインタ.
	WIHDR		*RcvWaitQue;	//!< タスクの受信待ち行列のポインタ.
	VP			ExtInfo;		//!< 拡張情報.
} WIMBFOBJ;

/*!
 *
 * @brief メッセージバッファ状態の参照用構造体.
 *
 */
typedef struct {
	INT			SndWaitId;		//!< メッセージバッファの送信待ち行列の先頭のタスクのID番号.
	INT			RcvWaitId;		//!< メッセージバッファの受信待ち行列の先頭のタスクのID番号.
	VP			ExtInfo;		//!< 拡張情報.
	INT			MsgSize;		//!< 次に受信されるメッセージのサイズ.
	INT			FreeSize;		//!< 空きバッファのサイズ.
} WIMBFSTAT;

/****************************************************************************
 *
 * 関数定義.
 *
 ****************************************************************************/
void	wi_InitMsgBuffer( void );
void	wi_QuitMsgBuffer( void );
ER		wi_CreateMsgBuffer( INT id, const WIMBFOBJ *obj );
ER		wi_DeleteMsgBuffer( INT id );
ER		wi_SendMsgBuffer( INT id, VP msg, int size, TMO tmout );
ER		wi_ReceiveMsgBuffer( INT id, VP msg, int *size, TMO tmout );
ER		wi_RefarenceMsgBuffer( INT id, WIMBFSTAT *sts );
void	wi_AllReleaseMsgBuffer( INT id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_MESSAGE_BUFFER_H__
/* End of file */
