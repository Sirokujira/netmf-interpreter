/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef nMruby_tTECSInitializer_TECSGEN_H
#define nMruby_tTECSInitializer_TECSGEN_H

/*
 * celltype          :  tTECSInitializer
 * global name       :  nMruby_tTECSInitializer
 * idx_is_id(actual) :  no(no)
 * singleton         :  no
 * has_CB            :  true
 * has_INIB          :  true
 * rom               :  yes
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "nMruby_sInitializeBridge_tecsgen.h"
#include "nMruby_sInitializeTECSBridge_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* セルタイプのIDX型 #_CTIX_# */
typedef struct tag_nMruby_tTECSInitializer_CB *nMruby_tTECSInitializer_IDX;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

#define nMruby_tTECSInitializer_ID_BASE        (1)  /* ID のベース  #_NIDB_# */
#define nMruby_tTECSInitializer_N_CELL        (1)  /* セルの個数  #_NCEL_# */

/* IDXの正当性チェックマクロ #_CVI_# */
#define nMruby_tTECSInitializer_VALID_IDX(IDX) (1)

/* 呼び口配列の大きさを得るマクロ #_NCPA_# */
#define N_CP_cInitialize(p_that)  ((p_that)->_inib->n_cInitialize)
#define NCP_cInitialize           (N_CP_cInitialize(p_cellcb))

/* セルCBを得るマクロ #_GCB_# */
#define nMruby_tTECSInitializer_GET_CELLCB(idx) (idx)



/* var アクセスマクロ #_VAM_# */
#define nMruby_tTECSInitializer_VAR_TECS(p_that)	((p_that)->TECS)

#define nMruby_tTECSInitializer_GET_TECS(p_that)	((p_that)->TECS)
#define nMruby_tTECSInitializer_SET_TECS(p_that,val)	((p_that)->TECS=(val))

 /* 呼び口関数マクロ #_CPM_# */
#define nMruby_tTECSInitializer_cInitialize_initializeBridge( p_that, subscript, mrb, TECS ) \
	  (p_that)->_inib->cInitialize[subscript]->VMT->initializeBridge__T( \
	   (p_that)->_inib->cInitialize[subscript], (mrb), (TECS) )

#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル INIB 型宣言 #_CIP_# */
typedef const struct tag_nMruby_tTECSInitializer_INIB {
    /* call port #_TCP_# */ 
    struct tag_nMruby_sInitializeTECSBridge_VDES *const*cInitialize;
    int_t n_cInitialize;
    /* call port #_NEP_# */ 
}  nMruby_tTECSInitializer_INIB;
/* セル CB 型宣言 #_CCTPA_# */
typedef struct tag_nMruby_tTECSInitializer_CB {
    nMruby_tTECSInitializer_INIB  *_inib;
    /* var #_VA_# */ 
    struct RClass * TECS;
}  nMruby_tTECSInitializer_CB;
extern nMruby_tTECSInitializer_CB  nMruby_tTECSInitializer_CB_tab[];

/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* nMruby_sInitializeBridge */
void         nMruby_tTECSInitializer_eInitialize_initializeBridge(nMruby_tTECSInitializer_IDX idx, const mrb_state* mrb);

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

/* IDXの正当性チェックマクロ（短縮形） #_CVIA_# */
#define VALID_IDX(IDX)  nMruby_tTECSInitializer_VALID_IDX(IDX)


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  nMruby_tTECSInitializer_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	nMruby_tTECSInitializer_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	nMruby_tTECSInitializer_IDX

#define tTECSInitializer_IDX  nMruby_tTECSInitializer_IDX


/* var アクセスマクロ(短縮形) #_VAMA_# */
#define VAR_TECS             nMruby_tTECSInitializer_VAR_TECS( p_cellcb )

/* 呼び口関数マクロ（短縮形）#_CPMA_# */
#define cInitialize_initializeBridge( subscript, mrb, TECS ) \
                      nMruby_tTECSInitializer_cInitialize_initializeBridge( p_cellcb, subscript, mrb, TECS ) 


/* 受け口関数マクロ（短縮形） #_EPM_# */
#define eInitialize_initializeBridge nMruby_tTECSInitializer_eInitialize_initializeBridge

/* イテレータコード (FOREACH_CELL)の生成 #_FEC_# */
#define FOREACH_CELL(i,p_cb)   \
    for( (i) = 0; (i) < nMruby_tTECSInitializer_N_CELL; (i)++ ){ \
       (p_cb) = &nMruby_tTECSInitializer_CB_tab[i];

#define END_FOREACH_CELL   }

/* CB 初期化マクロ #_CIM_# */
#define INITIALIZE_CB(p_that)\
	(p_that)->TECS = 0;
#define SET_CB_INIB_POINTER(i,p_that)\
	(p_that)->_inib = &nMruby_tTECSInitializer_INIB_tab[(i)];

#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* nMruby_tTECSInitializer_TECSGEN_H */
