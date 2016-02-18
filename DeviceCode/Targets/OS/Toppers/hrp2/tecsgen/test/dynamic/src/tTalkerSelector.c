/*
 * このファイルは tecsgen によりテンプレートとして自動生成されました
 * このファイルを編集して使用することが意図されていますが
 * tecsgen の再実行により上書きされてしまうため、通常
 *   gen/tTalkerSelector_template.c => src/tTalkerSelector.c
 * のように名前, フォルダを変更してから修正します
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 属性アクセスマクロ #_CAAM_#
 * name             char_t*          ATTR_name       
 *
 * 呼び口関数 #_TCPF_#
 * call port: cHello signature: sHello context:task 
 *   void           cHello_hello( subscript );
 *       subscript:  0...(NCP_cHello-1)
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "tTalkerSelector_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

/* 受け口関数 #_TEPF_# */
/* #[<ENTRY_PORT>]# eTalkerSelector
 * entry port: eTalkerSelector
 * signature:  sTalkerSelector
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eTalkerSelector_getTalker
 * name:         eTalkerSelector_getTalker
 * global_name:  tTalkerSelector_eTalkerSelector_getTalker
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eTalkerSelector_getTalker(CELLIDX idx, Descriptor( sHello )* talker)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */

}

/* #[<ENTRY_FUNC>]# eTalkerSelector_getNTalker
 * name:         eTalkerSelector_getNTalker
 * global_name:  tTalkerSelector_eTalkerSelector_getNTalker
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eTalkerSelector_getNTalker(CELLIDX idx, int_t* n)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */

}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
