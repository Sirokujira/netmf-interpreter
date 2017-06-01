/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_alarm_handler.c
 *
 *	@brief	Windows版 iTRONサービスコール (アラーム･ハンドラ).
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_alarm_handler.h"

/****************************************************************************
 *
 * ローカル変数定義.
 *
 ****************************************************************************/
static WIHDR	*ObjList;		//!< アラーム･ハンドラ･リストのポインタ.

/****************************************************************************/
/*!
 *	@brief	アラーム･ハンドラの初期処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_InitAlarmHadler( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	アラーム･ハンドラの終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_QuitAlarmHadler( void )
{
	WIHDR		*next_ptr;
	WIALMOBJ	*p = (WIALMOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! アラーム･ハンドラ･オブジェクト構造体を解放する.
		SAFE_RELEASE( p );

		//! 次のアラーム･ハンドラ･オブジェクト構造体を取り出す.
		p = (WIALMOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	アラーム･ハンドラ定義.
 *
 *	@param	[in]	no		アラーム･ハンドラ番号.
 *	@param	[in]	obj		アラーム･ハンドラ.オブジェクト構造体のポインタ.
 *	@param	[in]	ovr		TRUE = 登録済みIDに上書き.
 *
 *	@retval	エラーコード.
 */
ER		wi_DefineAlarmHadler( INT no, const WIALMOBJ *obj, BOOL ovr )
{
	ER			ercd;
	WIALMOBJ	*p;

	p = (WIALMOBJ *)wi_GetObject( no, ObjList );
	if( p ){
		//! 登録済みハンドラに上書き禁止の場合はエラー終了にする.
		if( !ovr ){
			return E_OBJ;
		}
		//! 既に登録しているハンドラ番号の場合は登録を上書きする.
		p->Attribute = obj->Attribute;
		p->AlmAdr    = obj->AlmAdr;
		p->TimeMode  = obj->TimeMode;
		p->AlmTime   = obj->AlmTime;
		p->ExtInfo   = obj->ExtInfo;
		p->Active    = obj->Active;
		return E_OK;
	}
	//! アラーム･ハンドラ･オブジェクトを作成する.
	p = (WIALMOBJ *)wi_CreateObject( no, TMAX_MAXALM, sizeof(WIALMOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストにアラーム･ハンドラを追加する.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	アラーム･ハンドラの削除.
 *
 *	@param	[in]	no		アラーム･ハンドラ番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_DeleteAlarmHadler( INT no )
{
	ER			ercd;
	WIALMOBJ	*p;

	//! アラーム･ハンドラ番号のオブジェクトを取得する.
	p = (WIALMOBJ *)wi_FindObject( no, TMAX_MAXALM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストから該当するアラーム･ハンドラを取り除く.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! アラーム･ハンドラ･オブジェクト構造体を解放する.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	アラーム･ハンドラの起動.
 *
 *	@param	[in]	no		アラーム･ハンドラ番号.
 *	@param	[in]	almtim	起動時刻.
 *
 *	@retval	エラーコード.
 */
ER		wi_StartAlarmHadler( INT no, DWORDLONG almtim )
{
	ER			ercd;
	WIALMOBJ	*p;

	//! アラーム･ハンドラ番号のオブジェクトを取得する.
	p = (WIALMOBJ *)wi_FindObject( no, TMAX_MAXALM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! アラーム･ハンドラの起動時刻を現在時刻からの相対時刻でセットする.
	p->AlmTime = wi_GetSystemTime() + almtim;

	//! アラーム･ハンドラの動作状態を「起動中」にする.
	p->Active  = TRUE;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	アラーム･ハンドラの停止.
 *
 *	@param	[in]	no		アラーム･ハンドラ番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_StopAlarmHadler( INT no )
{
	ER			ercd;
	WIALMOBJ	*p;

	//! アラーム･ハンドラ番号のオブジェクトを取得する.
	p = (WIALMOBJ *)wi_FindObject( no, TMAX_MAXALM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! アラーム･ハンドラの動作状態を「停止中」にする.
	p->Active = FALSE;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	アラーム･ハンドラの状態参照.
 *
 *	@param	[in]	no		アラーム･ハンドラ番号.
 *	@param	[out]	sts		アラーム･ハンドラ状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_RefarenceAlarmHadler( INT no, WIALMSTAT *sts )
{
	ER			ercd;
	WIALMOBJ	*p;
	DWORDLONG	now_time;

	//! アラーム･ハンドラ番号のオブジェクトを取得する.
	p = (WIALMOBJ *)wi_FindObject( no, TMAX_MAXALM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 現在時刻を取得する.
	now_time = wi_GetSystemTime();

	//! 起動時刻までの時間を計算する.
	if( now_time >= p->AlmTime ){
		sts->LeftTime = 0;
	}else{
		sts->LeftTime = p->AlmTime - now_time;
	}
	//! アラーム･ハンドラの状態を構造体にセットする.
	sts->Active  = p->Active;
	sts->ExtInfo = p->ExtInfo;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	アラーム･ハンドラの周期処理.
 *
 *	@param	[in]	now_time	現在時刻.
 *
 *	@retval	なし.
 */
void	wi_CallAlarmHandler( DWORDLONG now_time )
{
	WIALMOBJ *next_ptr;
	WIALMOBJ *p = (WIALMOBJ *)ObjList;
	while( p ){

		next_ptr = (WIALMOBJ *)p->Hdr.Next;

		if( now_time >= p->AlmTime ){
			if( p->Active ){
				if( p->AlmAdr ){
					p->AlmAdr();
				}
				p->Active = FALSE;
			}
			//! リストから該当するアラーム･ハンドラを取り除く.
			wi_DelObject( (WIHDR *)p, &ObjList );

			//! アラーム･ハンドラ･オブジェクト構造体を解放する.
			SAFE_RELEASE( p );
		}
		p = next_ptr;
	}
}

/* End of file */
