/*
 * このファイルは tecsgen によりテンプレートとして自動生成されました
 * このファイルを編集して使用することが意図されていますが
 * tecsgen の再実行により上書きされてしまうため、通常
 *   gen/tBalancer_template.c => src/tBalancer.c
 * のように名前, フォルダを変更してから修正します
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "tBalancer_tecsgen.h"
#include "balancer.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

/* 受け口関数 #_TEPF_# */
/* #[<ENTRY_PORT>]# eBalancer
 * entry port: eBalancer
 * signature:  sBalancer
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eBalancer_control
 * name:         eBalancer_control
 * global_name:  tBalancer_eBalancer_control
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eBalancer_control(float32_t forward, float32_t turn, float32_t gyro, float32_t gyroOffset, float32_t leftRevolution, float32_t rightRevolution, float32_t battery, int8_t* pwm_l, int8_t* pwm_r)
{
	balance_control(forward,
			turn,
			gyro,
			gyroOffset,
			leftRevolution,
			rightRevolution,
			battery,
			pwm_l,
			pwm_r);	
}

/* #[<ENTRY_FUNC>]# eBalancer_init
 * name:         eBalancer_init
 * global_name:  tBalancer_eBalancer_init
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eBalancer_init()
{
	// 倒立制御用ライブラリ関数を呼び出す
	balance_init();
}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
