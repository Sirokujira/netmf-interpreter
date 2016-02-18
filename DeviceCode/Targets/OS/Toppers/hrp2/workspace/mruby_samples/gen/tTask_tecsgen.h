/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tTask_TECSGEN_H
#define tTask_TECSGEN_H

/*
 * celltype          :  tTask
 * global name       :  tTask
 * idx_is_id(actual) :  no(yes)
 * singleton         :  no
 * has_CB            :  false
 * has_INIB          :  true
 * rom               :  yes
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sTask_tecsgen.h"
#include "siTask_tecsgen.h"
#include "sTaskBody_tecsgen.h"
#include "sTaskExceptionBody_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* セルタイプのIDX型 #_CTIX_# */
typedef ID tTask_IDX;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* 最適化のため参照するセルタイプの CB 型の定義を取込む #_ICT_# */
#ifndef  TOPPERS_CB_TYPE_ONLY
#define  tTask_CB_TYPE_ONLY
#define TOPPERS_CB_TYPE_ONLY
#endif  /* TOPPERS_CB_TYPE_ONLY */
#ifdef  tTask_CB_TYPE_ONLY
#undef TOPPERS_CB_TYPE_ONLY
#endif /* tTask_CB_TYPE_ONLY */
#define tTask_ID_BASE               (1)  /* ID のベース  #_NIDB_# */
#define tTask_N_CELL                (2)  /* セルの個数  #_NCEL_# */

/* IDXの正当性チェックマクロ #_CVI_# */
#define tTask_VALID_IDX(IDX) (tTask_ID_BASE <= (IDX) && (IDX) < tTask_ID_BASE+tTask_N_CELL)

/* optional 呼び口をテストするマクロ #_TOCP_# */
#define tTask_is_cExceptionBody_joined(p_that) \
	  (0)    /* not joined */

/* セルCBを得るマクロ #_GCB_# */
#define tTask_GET_CELLCB(idx) (tTask_CB_tab[(idx) - tTask_ID_BASE])

/* 属性アクセスマクロ #_AAM_# */
#define tTask_ATTR_id( p_that )	((p_that)->id)

#define tTask_GET_id(p_that)	((p_that)->id)



 /* 呼び口関数マクロ #_CPM_# */
#define tTask_cBody_main( p_that ) \
	  (p_that)->cBody->VMT->main__T( \
	   (p_that)->cBody )
#define tTask_cExceptionBody_main( p_that, pattern ) \
	  ((void (*)())0)()
	  /* optional no entry port joined */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル INIB 型宣言 #_CIP_# */
typedef const struct tag_tTask_INIB {
    /* call port #_TCP_# */ 
    struct tag_sTaskBody_VDES const*cBody;
    /* call port #_NEP_# */ 
    /* attribute(RO) #_ATO_# */ 
    ID             id;
}  tTask_INIB;

/* CB は存在しない。INIB を CB の代わりに使用するための define #_DCI_# */
#define tTask_CB_tab           tTask_INIB_tab
#define tTask_SINGLE_CELL_CB   tTask_SINGLE_CELL_INIB
#define tTask_CB               tTask_INIB
#define tag_tTask_CB           tag_tTask_INIB

extern tTask_CB  *tTask_CB_tab[];

/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sTask */
Inline ER           tTask_eTask_activate(tTask_IDX idx);
Inline ER_UINT      tTask_eTask_cancelActivate(tTask_IDX idx);
Inline ER           tTask_eTask_terminate(tTask_IDX idx);
Inline ER           tTask_eTask_changePriority(tTask_IDX idx, PRI priority);
Inline ER           tTask_eTask_getPriority(tTask_IDX idx, PRI* p_priority);
Inline ER           tTask_eTask_refer(tTask_IDX idx, T_RTSK* pk_taskStatus);
Inline ER           tTask_eTask_wakeup(tTask_IDX idx);
Inline ER_UINT      tTask_eTask_cancelWakeup(tTask_IDX idx);
Inline ER           tTask_eTask_releaseWait(tTask_IDX idx);
Inline ER           tTask_eTask_suspend(tTask_IDX idx);
Inline ER           tTask_eTask_resume(tTask_IDX idx);
Inline ER           tTask_eTask_raiseException(tTask_IDX idx, TEXPTN pattern);
Inline ER           tTask_eTask_referException(tTask_IDX idx, T_RTEX* pk_rtex);
Inline ER           tTask_eTask_startOverRunHandler(tTask_IDX idx, OVRTIM ovrtim);
Inline ER           tTask_eTask_stopOverRunHandler(tTask_IDX idx);
Inline ER           tTask_eTask_referOverRunHandler(tTask_IDX idx, T_ROVR* pk_rovr);
/* siTask */
Inline ER           tTask_eiTask_activate(tTask_IDX idx);
Inline ER           tTask_eiTask_wakeup(tTask_IDX idx);
Inline ER           tTask_eiTask_releaseWait(tTask_IDX idx);
Inline ER           tTask_eiTask_raiseException(tTask_IDX idx, TEXPTN pattern);
Inline ER           tTask_eiTask_disableWait(tTask_IDX idx);
Inline ER           tTask_eiTask_enableWait(tTask_IDX idx);
Inline ER           tTask_eiTask_startOverRunHandler(tTask_IDX idx, OVRTIM ovrtim);
Inline ER           tTask_eiTask_stopOverRunHandler(tTask_IDX idx);

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* IDXの正当性チェックマクロ（短縮形） #_CVIA_# */
#define VALID_IDX(IDX)  tTask_VALID_IDX(IDX)


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tTask_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tTask_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tTask_IDX


/* 属性アクセスマクロ(短縮形) #_AAMA_# */
#define ATTR_id              tTask_ATTR_id( p_cellcb )


/* 呼び口関数マクロ（短縮形）#_CPMA_# */
#define cBody_main( ) \
                      tTask_cBody_main( p_cellcb ) 
#define cExceptionBody_main( pattern ) \
                      tTask_cExceptionBody_main( p_cellcb, pattern ) 

/* optional 呼び口をテストするマクロ（短縮形） #_TOCPA_# */
#define is_cExceptionBody_joined()\
		tTask_is_cExceptionBody_joined(p_cellcb)

/* 受け口関数マクロ（短縮形） #_EPM_# */
#define eTask_activate   tTask_eTask_activate
#define eTask_cancelActivate tTask_eTask_cancelActivate
#define eTask_terminate  tTask_eTask_terminate
#define eTask_changePriority tTask_eTask_changePriority
#define eTask_getPriority tTask_eTask_getPriority
#define eTask_refer      tTask_eTask_refer
#define eTask_wakeup     tTask_eTask_wakeup
#define eTask_cancelWakeup tTask_eTask_cancelWakeup
#define eTask_releaseWait tTask_eTask_releaseWait
#define eTask_suspend    tTask_eTask_suspend
#define eTask_resume     tTask_eTask_resume
#define eTask_raiseException tTask_eTask_raiseException
#define eTask_referException tTask_eTask_referException
#define eTask_startOverRunHandler tTask_eTask_startOverRunHandler
#define eTask_stopOverRunHandler tTask_eTask_stopOverRunHandler
#define eTask_referOverRunHandler tTask_eTask_referOverRunHandler
#define eiTask_activate  tTask_eiTask_activate
#define eiTask_wakeup    tTask_eiTask_wakeup
#define eiTask_releaseWait tTask_eiTask_releaseWait
#define eiTask_raiseException tTask_eiTask_raiseException
#define eiTask_disableWait tTask_eiTask_disableWait
#define eiTask_enableWait tTask_eiTask_enableWait
#define eiTask_startOverRunHandler tTask_eiTask_startOverRunHandler
#define eiTask_stopOverRunHandler tTask_eiTask_stopOverRunHandler

/* イテレータコード (FOREACH_CELL)の生成 #_FEC_# */
#define FOREACH_CELL(i,p_cb)   \
    for( (i) = 0; (i) < tTask_N_CELL; (i)++ ){ \
       //(p_cb) = tTask_CB_tab[i];

#define END_FOREACH_CELL   }

/* CB 初期化マクロ #_CIM_# */
#define INITIALIZE_CB(p_that)
#define SET_CB_INIB_POINTER(i,p_that)\
	/* empty */
#ifndef TOPPERS_MACRO_ONLY

/* inline ヘッダの include #_INL_# */
#include "tTask_inline.h"

#endif /* TOPPERS_MACRO_ONLY */

#ifdef TOPPERS_CB_TYPE_ONLY

/* inline のための undef #_UDF_# */
#undef VALID_IDX
#undef GET_CELLCB
#undef CELLCB
#undef CELLIDX
#undef tTask_IDX
#undef FOREACH_CELL
#undef END_FOREACH_CELL
#undef INITIALIZE_CB
#undef SET_CB_INIB_POINTER
#undef ATTR_id
#undef tTask_ATTR_id
#undef tTask_GET_id
#undef ATTR_taskAttribute
#undef tTask_ATTR_taskAttribute
#undef tTask_GET_taskAttribute
#undef ATTR_exceptionAttribute
#undef tTask_ATTR_exceptionAttribute
#undef tTask_GET_exceptionAttribute
#undef ATTR_priority
#undef tTask_ATTR_priority
#undef tTask_GET_priority
#undef ATTR_stackSize
#undef tTask_ATTR_stackSize
#undef tTask_GET_stackSize
#undef ATTR_systemStackSize
#undef tTask_ATTR_systemStackSize
#undef tTask_GET_systemStackSize
#undef ATTR_userStackSize
#undef tTask_ATTR_userStackSize
#undef tTask_GET_userStackSize
#undef ATTR_accessPattern
#undef tTask_ATTR_accessPattern
#undef tTask_GET_accessPattern
#undef tTask_cBody_main
#undef cBody_main
#undef tTask_cExceptionBody_main
#undef cExceptionBody_main
#undef eTask_activate
#undef eTask_cancelActivate
#undef eTask_terminate
#undef eTask_changePriority
#undef eTask_getPriority
#undef eTask_refer
#undef eTask_wakeup
#undef eTask_cancelWakeup
#undef eTask_releaseWait
#undef eTask_suspend
#undef eTask_resume
#undef eTask_raiseException
#undef eTask_referException
#undef eTask_startOverRunHandler
#undef eTask_stopOverRunHandler
#undef eTask_referOverRunHandler
#undef eiTask_activate
#undef eiTask_wakeup
#undef eiTask_releaseWait
#undef eiTask_raiseException
#undef eiTask_disableWait
#undef eiTask_enableWait
#undef eiTask_startOverRunHandler
#undef eiTask_stopOverRunHandler
#endif /* TOPPERS_CB_TYPE_ONLY */

#endif /* tTask_TECSGEN_H */
