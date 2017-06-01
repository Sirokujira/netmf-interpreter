/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_variable_mempool.h
 *
 *	@brief	Windows版 iTRONサービスコール (可変長メモリプール).
 *
 *	@author	金澤 宣明
 */
#ifndef	__WI_VARIABLE_MEMPOOL_H__
#define	__WI_VARIABLE_MEMPOOL_H__

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
 * @brief 可変長メモリ･オブジェクト構造体.
 *
 */
typedef struct {
	WIHDR		Hdr;				//!< オブジェクト･ヘッダ.
	VP			ExtInfo;			//!< 拡張情報.
	ATR			Attribute; 			//!< 可変長メモリプール属性.
	INT			MemSize;			//!< 可変長メモリプールのサイズ.
	BYTE		*MemBuf;			//!< 可変長メモリプールのデータバッファのポインタ.
	WIHDR		*WaitQue;			//!< タスクの待ち行列のポインタ.
} WIMPLOBJ;

/*!
 *
 * @brief 可変長メモリの状態参照用構造体.
 *
 */
typedef struct {
	INT			WaitId;				//!< 待ち行列の先頭のタスクのID番号.
	INT			TotalFreeSize;		//!< 空き領域の合計サイズ.
	INT			MaxFreeSize;		//!< 最大の連続空き領域のサイズ.
	VP			ExtInfo;			//!< 拡張情報.
} WIMPLSTAT;

/****************************************************************************
 *
 * 関数定義.
 *
 ****************************************************************************/
void	wi_InitVarMemPool( void );
void	wi_QuitVarMemPool( void );
ER		wi_CreateVarMemPool( INT id, const WIMPLOBJ *obj );
ER		wi_DeleteVarMemPool( INT id );
ER		wi_GetVarMemPool( INT id, VP adr, INT size, TMO tmout );
ER		wi_ReleaseVarMemPool( INT id, VP adr );
ER		wi_RefarenceVarMemPool( INT id, WIMPLSTAT *sts );
void	wi_AllReleaseVarMemPool( INT id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_VARIABLE_MEMPOOL_H__
/* End of file */
