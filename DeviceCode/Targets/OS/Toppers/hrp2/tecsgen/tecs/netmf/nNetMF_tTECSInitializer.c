/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 属性アクセスマクロ #_CAAM_#
 * TECS             struct RClass *  VAR_TECS        
 *
 * 呼び口関数 #_TCPF_#
 * call port : cInitialize  signature: nNetMF_sInitializeTECSBridge context: task
 *   void           cInitialize_initializeBridge( subscript, const netmf_state* netmf, const struct RClass * TECS );
 *       subscript:  0...(NCP_cInitialize-1)
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "nNetMF_tTECSInitializer_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

/* 受け口関数 #_TEPF_# */
/* #[<ENTRY_PORT>]# eInitialize
 * entry port: eInitialize
 * signature:  nNetMF_sInitializeBridge
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eInitialize_initializeBridge
 * name:         eInitialize_initializeBridge
 * global_name:  nNetMF_tTECSInitializer_eInitialize_initializeBridge
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eInitialize_initializeBridge(CELLIDX idx, const netmf_state* netmf)
{
	CELLCB	*p_cellcb;
	int      i;
	struct RClass *TECS;

	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */
	VAR_TECS = netmf_define_module( (netmf_state *)netmf, "TECS" );
	// netmf: const netmf_state * => netmf_state *

	for( i = 0; i < NCP_cInitialize; i++ )
		cInitialize_initializeBridge( i, (netmf_state*)netmf, VAR_TECS );
}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
