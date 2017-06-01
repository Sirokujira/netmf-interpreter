/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_cycle_handler.c
 *
 *	@brief	Windows版 iTRONサービスコール (周期ハンドラ).
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_cycle_handler.h"

/****************************************************************************
 *
 * ローカル変数定義.
 *
 ****************************************************************************/
static WIHDR		*ObjList;		//!< 周期ハンドラ･リストのポインタ.

/****************************************************************************/
/*!
 *	@brief	周期ハンドラの初期処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_InitCycleHadler( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	周期ハンドラの終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	wi_QuitCycleHadler( void )
{
	WIHDR		*next_ptr;
	WICYCOBJ	*p = (WICYCOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! 周期ハンドラ･オブジェクト構造体を解放する.
		SAFE_RELEASE( p );

		//! 次の周期ハンドラ･オブジェクト構造体を取り出す.
		p = (WICYCOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	周期ハンドラ定義.
 *
 *	@param	[in]	no		周期ハンドラ番号.
 *	@param	[in]	obj		周期ハンドラ･オブジェクト構造体のポインタ.
 *	@param	[in]	ovr		TRUE = 登録済みIDに上書き.
 *
 *	@retval	エラーコード.
 */
ER		wi_DefineCycleHadler( INT no, const WICYCOBJ *obj, BOOL ovr )
{
	ER			ercd;
	WICYCOBJ	*p;

	p = (WICYCOBJ *)wi_GetObject( no, ObjList );
	if( p ){
		//! 登録済みハンドラに上書き禁止の場合はエラー終了にする.
		if( !ovr ){
			return E_OBJ;
		}
		//! 既に登録しているハンドラ番号の場合は登録を上書きする.
		p->Hdr.Id    = no;
		p->Attribute = obj->Attribute;
		p->CycAdr    = obj->CycAdr;
		p->Active    = obj->Active;
		p->ExtInfo   = obj->ExtInfo;
		p->CycleTime = obj->CycleTime;
		p->StartTime = wi_GetSystemTime();
		return E_OK;
	}
	//! 周期ハンドラ･オブジェクトを作成する.
	p = (WICYCOBJ *)wi_CreateObject( no, TMAX_MAXCYC, sizeof(WICYCOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストに周期ハンドラを追加する.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	周期ハンドラの削除.
 *
 *	@param	[in]	no		周期ハンドラ番号.
 *
 *	@retval	エラーコード.
 */
ER		wi_DeleteCycleHadler( INT no )
{
	ER			ercd;
	WICYCOBJ	*p;

	//! 周期ハンドラ番号のオブジェクトを取得する.
	p = (WICYCOBJ *)wi_FindObject( no, TMAX_MAXCYC, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! リストから該当する周期ハンドラを取り除く.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! 周期ハンドラ･オブジェクト構造体を解放する.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	周期ハンドラの活性制御.
 *
 *	@param	[in]	no		周期ハンドラ番号.
 *	@param	[in]	act		TRUE = 起動 / FALSE = 停止.
 *	@param	[in]	init	TRUE = 初期化要求.
 *
 *	@retval	エラーコード.
 */
ER		wi_ActionCycleHadler( INT no, BOOL act, BOOL init )
{
	ER			ercd;
	WICYCOBJ	*p;

	//! 周期ハンドラ番号のオブジェクトを取得する.
	p = (WICYCOBJ *)wi_FindObject( no, TMAX_MAXCYC, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 周期ハンドラの活性情報をセットする.
	p->Active = act;

	//! 周期カウンタを初期化する.
	if( init ){
		p->StartTime = wi_GetSystemTime();
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	周期ハンドラの状態参照.
 *
 *	@param	[in]	no		周期ハンドラ番号.
 *	@param	[out]	sts		周期ハンドラ状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wi_RefarenceCycleHadler( INT no, WICYCSTAT *sts )
{
	ER			ercd;
	WICYCOBJ	*p;
	DWORDLONG	now_time;

	//! 周期ハンドラ番号のオブジェクトを取得する.
	p = (WICYCOBJ *)wi_FindObject( no, TMAX_MAXCYC, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! 現在時刻を取得する.
	now_time = wi_GetSystemTime();

	//! 起動時刻までの時間を計算する.
	if( (now_time - p->StartTime) >= p->CycleTime ){
		sts->LeftTime = 0;
	}else{
		sts->LeftTime = p->CycleTime - (now_time - p->StartTime);
	}
	//! 周期ハンドラの状態を構造体にセットする.
	sts->Active  = p->Active;
	sts->ExtInfo = p->ExtInfo;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	周期ハンドラのタイマ処理.
 *
 *	@param	[in]	now_time	現在時刻.
 *
 *	@retval	なし.
 */
void	wi_CycleTimer( DWORDLONG now_time )
{
	WICYCOBJ *p = (WICYCOBJ *)ObjList;

	while( p ){
		if( p->Active ){
			//! 周期カウンタが周期時間経過したかどうかをチェックする.
			if( (now_time - p->StartTime) >= p->CycleTime ){

				//! 周期ハンドラを呼び出す.
				if( p->CycAdr ){
					p->CycAdr();
				}
				//! 周期ハンドラを呼び出した時刻を保存する.
				p->StartTime = now_time;
			}
		}
		//! リストから次の周期ハンドラを取り出す.
		p = (WICYCOBJ *)(p->Hdr.Next);
	}
}

/* End of file */
