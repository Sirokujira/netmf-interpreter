/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef nMruby_tsTouchSensor_TECSGEN_H
#define nMruby_tsTouchSensor_TECSGEN_H

/*
 * celltype          :  tsTouchSensor
 * global name       :  nMruby_tsTouchSensor
 * idx_is_id(actual) :  yes(no)
 * singleton         :  no
 * has_CB            :  false
 * has_INIB          :  true
 * rom               :  yes
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sTouchSensor_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* セルタイプのIDX型 #_CTIX_# */
typedef const struct tag_nMruby_tsTouchSensor_INIB *nMruby_tsTouchSensor_IDX;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* 最適化のため参照するセルタイプの CB 型の定義を取込む #_ICT_# */
#ifndef  TOPPERS_CB_TYPE_ONLY
#define  nMruby_tsTouchSensor_CB_TYPE_ONLY
#define TOPPERS_CB_TYPE_ONLY
#endif  /* TOPPERS_CB_TYPE_ONLY */
#include "tTouchSensor_tecsgen.h"
#ifdef  nMruby_tsTouchSensor_CB_TYPE_ONLY
#undef TOPPERS_CB_TYPE_ONLY
#endif /* nMruby_tsTouchSensor_CB_TYPE_ONLY */
#ifndef TOPPERS_CB_TYPE_ONLY

#define nMruby_tsTouchSensor_ID_BASE        (1)  /* ID のベース  #_NIDB_# */
#define nMruby_tsTouchSensor_N_CELL        (4)  /* セルの個数  #_NCEL_# */

/* IDXの正当性チェックマクロ #_CVI_# */
#define nMruby_tsTouchSensor_VALID_IDX(IDX) (1)


/* セルCBを得るマクロ #_GCB_# */
#define nMruby_tsTouchSensor_GET_CELLCB(idx) (idx)
 /* 呼び口関数マクロ #_CPM_# */
#define nMruby_tsTouchSensor_cTECS_isPressed( p_that ) \
	  tTouchSensor_eTouchSensor_isPressed( \
	   (p_that)->cTECS )
#define nMruby_tsTouchSensor_cTECS_initializePort( p_that ) \
	  tTouchSensor_eTouchSensor_initializePort( \
	   (p_that)->cTECS )

#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル INIB 型宣言 #_CIP_# */
typedef const struct tag_nMruby_tsTouchSensor_INIB {
    /* call port #_TCP_# */ 
    const struct tag_tTouchSensor_INIB * cTECS;
}  nMruby_tsTouchSensor_INIB;

/* CB は存在しない。INIB を CB の代わりに使用するための define #_DCI_# */
#define nMruby_tsTouchSensor_CB_tab           nMruby_tsTouchSensor_INIB_tab
#define nMruby_tsTouchSensor_SINGLE_CELL_CB   nMruby_tsTouchSensor_SINGLE_CELL_INIB
#define nMruby_tsTouchSensor_CB               nMruby_tsTouchSensor_INIB
#define tag_nMruby_tsTouchSensor_CB           tag_nMruby_tsTouchSensor_INIB

extern nMruby_tsTouchSensor_CB  nMruby_tsTouchSensor_CB_tab[];

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

/* IDXの正当性チェックマクロ（短縮形） #_CVIA_# */
#define VALID_IDX(IDX)  nMruby_tsTouchSensor_VALID_IDX(IDX)


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  nMruby_tsTouchSensor_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	nMruby_tsTouchSensor_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	nMruby_tsTouchSensor_IDX

#define tsTouchSensor_IDX  nMruby_tsTouchSensor_IDX
/* 呼び口関数マクロ（短縮形）#_CPMA_# */
#define cTECS_isPressed( ) \
                      nMruby_tsTouchSensor_cTECS_isPressed( p_cellcb ) 
#define cTECS_initializePort( ) \
                      nMruby_tsTouchSensor_cTECS_initializePort( p_cellcb ) 

/* イテレータコード (FOREACH_CELL)の生成 #_FEC_# */
#define FOREACH_CELL(i,p_cb)   \
    for( (i) = 0; (i) < nMruby_tsTouchSensor_N_CELL; (i)++ ){ \
       //(p_cb) = &nMruby_tsTouchSensor_CB_tab[i];

#define END_FOREACH_CELL   }

/* CB 初期化マクロ #_CIM_# */
#define INITIALIZE_CB(p_that)
#define SET_CB_INIB_POINTER(i,p_that)\
	/* empty */
#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* nMruby_tsTouchSensor_TECSGEN_H */
