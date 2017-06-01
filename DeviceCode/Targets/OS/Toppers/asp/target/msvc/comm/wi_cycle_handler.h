/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_cycle_handler.h
 *
 *	@brief	Windows版 iTRONサービスコール (周期ハンドラ).
 *
 *	@author	金澤 宣明
 */
#ifndef	__WI_CYCLE_HANDLER_H__
#define	__WI_CYCLE_HANDLER_H__

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
 * @brief 周期ハンドラ･リソース構造体.
 *
 */
typedef struct {
	WIHDR			Hdr;			//!< オブジェクト･ヘッダ.
	ATR				Attribute; 		//!< 周期ハンドラ属性.
	FP				CycAdr;			//!< 周期ハンドラのアドレス.
	BOOL			Active;			//!< 周期ハンドラの活性状態.
	DWORDLONG		CycleTime;		//!< 周期起動時間間隔.
	DWORDLONG		StartTime;		//!< 最後に周期ハンドラを呼び出した時刻.
	DWORDLONG		CyclePhs; 		//!< 周期起動位相.
	VP				ExtInfo;		//!< 拡張情報.
} WICYCOBJ;

/*!
 *
 * @brief 周期ハンドラ状態の参照用構造体.
 *
 */
typedef struct {
	VP			ExtInfo;			//!< 拡張情報.
	DWORDLONG	LeftTime; 			//!< 次の起動周期までの時間.
	BOOL		Active;				//!< 周期ハンドラの活性状態.
} WICYCSTAT;


/****************************************************************************
 *
 * 関数定義.
 *
 ****************************************************************************/
void	wi_InitCycleHadler( void );
void	wi_QuitCycleHadler( void );
ER		wi_DefineCycleHadler( INT no, const WICYCOBJ *obj, BOOL ovr );
ER		wi_DeleteCycleHadler( INT no );
ER		wi_ActionCycleHadler( INT no, BOOL act, BOOL init );
ER		wi_RefarenceCycleHadler( INT no, WICYCSTAT *sts );
void	wi_CycleTimer( DWORDLONG now_time );

#ifdef __cplusplus
}
#endif
#endif	// __WI_CYCLE_HANDLER_H__
/* End of file */
