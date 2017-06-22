/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  @(#) $Id: target_stddef.h 107 2012-09-10 12:15:27Z nagasima $
 */

/*
 *  t_stddef.hのターゲット依存部（CQ-STARM用）
 *
 *  このインクルードファイルは，t_stddef.hの先頭でインクルードされる．
 *  他のファイルからは直接インクルードすることはない．他のインクルード
 *  ファイルに先立って処理されるため，他のインクルードファイルに依存し
 *  てはならない．
 */

#ifndef TOPPERS_TARGET_STDDEF_H
#define TOPPERS_TARGET_STDDEF_H

/*
 *  ターゲットを識別するためのマクロの定義
 */
#define TOPPERS_CQSTARM			/* システム略称 */


/*
 *  開発環境で共通な定義
 *
 *  開発環境でstdint.hが用意されている場合には，TOPPERS_STDINT_TYPE1の
 *  マクロ定義を削除し，stdint.hをインクルードすればよい．
 */
#define TOPPERS_STDINT_TYPE1
#define TOPPERS_STDFLOAT_TYPE1

#ifdef __GNUC__

#include "gcc/tool_stddef.h"

/*
 *  コア依存で共通な定義
 */
#include "arm_m_gcc/common/core_stddef.h"


#ifndef TOPPERS_MACRO_ONLY

/*
 *  アサーションの失敗時の実行中断処理（T.B.D）
 */
Inline void
TOPPERS_assert_abort(void)
{
    while(1);
}

#endif /* TOPPERS_MACRO_ONLY */

#else /*__GNUC__*/

#include "msvc/tool_stddef.h"

/*
 *  コアで共通な定義
 */
#include "arm_m_msvc/common/core_stddef.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif
/*
 *  アサーションの失敗時の実行中断処理（T.B.D）
 */
extern void TOPPERS_assert_abort(void);

#ifdef __cplusplus
}
#endif

#endif /* TOPPERS_MACRO_ONLY */

#endif /* __GNUC__ */

#endif /* TOPPERS_TARGET_STDDEF_H */