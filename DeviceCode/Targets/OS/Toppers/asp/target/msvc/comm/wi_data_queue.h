/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_data_queue.h
 *
 *	@brief	Windows版 iTRONサービスコール (データキュー).
 *
 *	@author	金澤 宣明
 */
#ifndef	__WI_DATA_QUEUE_H__
#define	__WI_DATA_QUEUE_H__

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
 * @brief データキュー･オブジェクト構造体.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< オブジェクト･ヘッダ.
	ATR			Attribute;		//!< データキュー属性.
	UINT		QueSize;		//!< データキュー領域の個数.
	DWORD		*QueBuf;		//!< データキュー領域の先頭アドレス.
	DWORD		GetPos;			//!< メールの読み出し位置.
	DWORD		PutPos;			//!< メールの書き出し位置.
	WIHDR		*SndWaitQue;	//!< タスクの送信待ち行列のポインタ.
	WIHDR		*RcvWaitQue;	//!< タスクの受信待ち行列のポインタ.
} WIDTQOBJ;

/*!
 *
 * @brief データキュー状態の参照用構造体.
 *
 */
typedef struct {
	INT			SndWaitId;			//!< データキューの送信待ち行列の先頭のタスクのID番号.
	INT			RcvWaitId;			//!< データキューの受信待ち行列の先頭のタスクのID番号.
	INT			DataCnt;			//!< データキューに入っているデータ数.
} WIDTQSTAT;

/****************************************************************************
 *
 * 関数定義.
 *
 ****************************************************************************/
void	wi_InitDataQueue( void );
void	wi_QuitDataQueue( void );
ER		wi_CreateDataQueue( INT id, const WIDTQOBJ *obj );
ER		wi_DeleteDataQueue( INT id );
ER		wi_SendDataQueue( INT id, DWORD data, TMO tmout );
ER		wi_ForceSendDataQueue( INT id, DWORD data );
ER		wi_ReceiveDataQueue( INT id, DWORD *data, TMO tmout );
ER		wi_RefarenceDataQueue(  INT id, WIDTQSTAT *sts );
void	wi_AllReleaseDataQueue( INT id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_DATA_QUEUE_H__
/* End of file */
