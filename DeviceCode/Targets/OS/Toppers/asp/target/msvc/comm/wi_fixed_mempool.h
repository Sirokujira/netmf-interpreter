/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_fixed_mempool.h
 *
 *	@brief	Windows版 iTRONサービスコール (固定長メモリプール).
 *
 *	@author	金澤 宣明
 */
#ifndef	__WI_FIXED_MEMPOOL_H__
#define	__WI_FIXED_MEMPOOL_H__

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
 * @brief 固定長メモリプール･オブジェクト構造体.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< オブジェクト･ヘッダ.
	ATR			Attribute; 		//!< 固定長メモリプールの属性.
	INT			BlockCnt; 		//!< 固定長メモリプール全体のブロック数.
	INT			BlockSize;		//!< 固定長メモリブロックのサイズ.
	BYTE*		MemBuf;			//!< メモリバッファのポインタ.
	WIHDR		*FreeQue;		//!< 未使用の固定長メモリブロック･リンクのポインタ.
	WIHDR		*UsedQue;		//!< 貸し出し中の固定長メモリブロック･リンクのポインタ.
	WIHDR		*WaitQue;		//!< タスクの待ち行列のポインタ.
	VP			ExtInfo;		//!< 拡張情報.
} WIMPFOBJ;

/*!
 *
 * @brief 固定長メモリプールの状態参照用構造体.
 *
 */
typedef struct {
	INT			WaitId;				//!< メモリブロック獲得待ち行列の先頭のタスクのID番号.
	INT			FreeBlock;			//!< 空きブロックの個数.
	VP			ExtInfo;			//!< 拡張情報.
} WIMPFSTAT;

/****************************************************************************
 *
 * 関数定義.
 *
 ****************************************************************************/
void	wi_InitFixedMemPool( void );
void	wi_QuitFixedMemPool( void );
ER		wi_CreateFixedMemPool( INT id, const WIMPFOBJ *obj );
ER		wi_DeleteFixedMemPool( INT id );
ER		wi_GetFixedMemPool( INT id, VP buf, TMO tmout );
ER		wi_ReleaseFixedMemPool( INT id, VP blf );
ER		wi_RefarenceFixedMemPool( INT id, WIMPFSTAT *sts );
void	wi_AllReleaseFixedMemPool( INT task_id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_FIXED_MEMPOOL_H__
/* End of file */
