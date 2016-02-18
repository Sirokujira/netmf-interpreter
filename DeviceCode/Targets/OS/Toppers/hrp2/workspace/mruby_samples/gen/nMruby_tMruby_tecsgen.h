/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef nMruby_tMruby_TECSGEN_H
#define nMruby_tMruby_TECSGEN_H

/*
 * celltype          :  tMruby
 * global name       :  nMruby_tMruby
 * idx_is_id(actual) :  no(no)
 * singleton         :  no
 * has_CB            :  false
 * has_INIB          :  true
 * rom               :  yes
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sTaskBody_tecsgen.h"
#include "nMruby_sInitializeBridge_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* セルタイプのIDX型 #_CTIX_# */
typedef const struct tag_nMruby_tMruby_INIB *nMruby_tMruby_IDX;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* 最適化のため参照するセルタイプの CB 型の定義を取込む #_ICT_# */
#ifndef  TOPPERS_CB_TYPE_ONLY
#define  nMruby_tMruby_CB_TYPE_ONLY
#define TOPPERS_CB_TYPE_ONLY
#endif  /* TOPPERS_CB_TYPE_ONLY */
#include "nMruby_tTECSInitializer_tecsgen.h"
#ifdef  nMruby_tMruby_CB_TYPE_ONLY
#undef TOPPERS_CB_TYPE_ONLY
#endif /* nMruby_tMruby_CB_TYPE_ONLY */
#ifndef TOPPERS_CB_TYPE_ONLY

#define nMruby_tMruby_ID_BASE        (1)  /* ID のベース  #_NIDB_# */
#define nMruby_tMruby_N_CELL        (1)  /* セルの個数  #_NCEL_# */

/* IDXの正当性チェックマクロ #_CVI_# */
#define nMruby_tMruby_VALID_IDX(IDX) (1)

/* optional 呼び口をテストするマクロ #_TOCP_# */
#define nMruby_tMruby_is_cInit_joined(p_that) \
	  (1)

/* セルCBを得るマクロ #_GCB_# */
#define nMruby_tMruby_GET_CELLCB(idx) (idx)

/* 属性アクセスマクロ #_AAM_# */
#define nMruby_tMruby_ATTR_irep( p_that )	((p_that)->irep)

#define nMruby_tMruby_GET_irep(p_that)	((p_that)->irep)



 /* 呼び口関数マクロ #_CPM_# */
#define nMruby_tMruby_cInit_initializeBridge( p_that, mrb ) \
	  nMruby_tTECSInitializer_eInitialize_initializeBridge( \
	   &nMruby_tTECSInitializer_CB_tab[0], (mrb) )

#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル INIB 型宣言 #_CIP_# */
typedef const struct tag_nMruby_tMruby_INIB {
    /* call port #_TCP_# */ 
    /* call port #_NEP_# */ 
    /* attribute(RO) #_ATO_# */ 
    char_t*        irep;
}  nMruby_tMruby_INIB;

/* CB は存在しない。INIB を CB の代わりに使用するための define #_DCI_# */
#define nMruby_tMruby_CB_tab           nMruby_tMruby_INIB_tab
#define nMruby_tMruby_SINGLE_CELL_CB   nMruby_tMruby_SINGLE_CELL_INIB
#define nMruby_tMruby_CB               nMruby_tMruby_INIB
#define tag_nMruby_tMruby_CB           tag_nMruby_tMruby_INIB

extern nMruby_tMruby_CB  nMruby_tMruby_CB_tab[];

/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sTaskBody */
void         nMruby_tMruby_eMrubyBody_main(nMruby_tMruby_IDX idx);

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */
/* eMrubyBody */
void           nMruby_tMruby_eMrubyBody_main_skel( const struct tag_sTaskBody_VDES *epd);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

/* IDXの正当性チェックマクロ（短縮形） #_CVIA_# */
#define VALID_IDX(IDX)  nMruby_tMruby_VALID_IDX(IDX)


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  nMruby_tMruby_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	nMruby_tMruby_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	nMruby_tMruby_IDX

#define tMruby_IDX  nMruby_tMruby_IDX

/* 属性アクセスマクロ(短縮形) #_AAMA_# */
#define ATTR_irep            nMruby_tMruby_ATTR_irep( p_cellcb )


/* 呼び口関数マクロ（短縮形）#_CPMA_# */
#define cInit_initializeBridge( mrb ) \
                      nMruby_tMruby_cInit_initializeBridge( p_cellcb, mrb ) 

/* optional 呼び口をテストするマクロ（短縮形） #_TOCPA_# */
#define is_cInit_joined()\
		nMruby_tMruby_is_cInit_joined(p_cellcb)

/* 受け口関数マクロ（短縮形） #_EPM_# */
#define eMrubyBody_main  nMruby_tMruby_eMrubyBody_main

/* イテレータコード (FOREACH_CELL)の生成 #_FEC_# */
#define FOREACH_CELL(i,p_cb)   \
    for( (i) = 0; (i) < nMruby_tMruby_N_CELL; (i)++ ){ \
       //(p_cb) = &nMruby_tMruby_CB_tab[i];

#define END_FOREACH_CELL   }

/* CB 初期化マクロ #_CIM_# */
#define INITIALIZE_CB(p_that)
#define SET_CB_INIB_POINTER(i,p_that)\
	/* empty */
#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* nMruby_tMruby_TECSGEN_H */
