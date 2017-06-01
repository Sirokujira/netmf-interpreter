/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_alarm_handler.h
 *
 *	@brief	Windows版 iTRONサービスコール (アラーム･ハンドラ).
 *
 *	@author	金澤 宣明
 */
#ifndef	__WI_ALARM_HANDLER_H__
#define	__WI_ALARM_HANDLER_H__

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
 * @brief アラーム･ハンドラ.オブジェクト構造体.
 *
 */
typedef struct {
	WIHDR		Hdr;				//!< オブジェクト･ヘッダ.
	ATR			Attribute; 			//!< アラーム･ハンドラ属性.
	FP			AlmAdr;				//!< アラーム･ハンドラのアドレス.
	BOOL		Active;				//!< アラーム･ハンドラの起動状態.
	UINT		TimeMode;			//!< 起動時刻指定モード.
	DWORDLONG	AlmTime; 			//!< 起動時刻.
	VP			ExtInfo;			//!< 拡張情報.
} WIALMOBJ;

/*!
 *
 * @brief アラーム･ハンドラ状態の参照用構造体.
 *
 */
typedef struct {
	DWORDLONG	LeftTime; 			//!< 起動時刻までの時間.
	BOOL		Active;				//!< アラーム･ハンドラの起動状態.
	VP			ExtInfo;			//!< 拡張情報.
} WIALMSTAT;

/****************************************************************************
 *
 * 関数定義.
 *
 ****************************************************************************/
void	wi_InitAlarmHadler( void );
void	wi_QuitAlarmHadler( void );
ER		wi_DefineAlarmHadler( INT no, const WIALMOBJ *obj, BOOL ovr );
ER		wi_DeleteAlarmHadler( INT no );
ER		wi_StartAlarmHadler( INT no, DWORDLONG almtim );
ER		wi_StopAlarmHadler( INT no );
ER		wi_RefarenceAlarmHadler( INT no, WIALMSTAT *sts );
void	wi_CallAlarmHandler( DWORDLONG now_time );

#ifdef __cplusplus
}
#endif
#endif	// __WI_ALARM_HANDLER_H__
/* End of file */
