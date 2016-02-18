/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tTouchSensor_TECSGEN_H
#define tTouchSensor_TECSGEN_H

/*
 * celltype          :  tTouchSensor
 * global name       :  tTouchSensor
 * idx_is_id(actual) :  no(no)
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
typedef const struct tag_tTouchSensor_INIB *tTouchSensor_IDX;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

#define tTouchSensor_ID_BASE        (1)  /* ID のベース  #_NIDB_# */
#define tTouchSensor_N_CELL         (4)  /* セルの個数  #_NCEL_# */

/* IDXの正当性チェックマクロ #_CVI_# */
#define tTouchSensor_VALID_IDX(IDX) (1)


/* セルCBを得るマクロ #_GCB_# */
#define tTouchSensor_GET_CELLCB(idx) (idx)

/* 属性アクセスマクロ #_AAM_# */
#define tTouchSensor_ATTR_port( p_that )	((p_that)->port)

#define tTouchSensor_GET_port(p_that)	((p_that)->port)



#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル INIB 型宣言 #_CIP_# */
typedef const struct tag_tTouchSensor_INIB {
    /* call port #_NEP_# */ 
    /* attribute(RO) #_ATO_# */ 
    int32_t        port;
}  tTouchSensor_INIB;

/* CB は存在しない。INIB を CB の代わりに使用するための define #_DCI_# */
#define tTouchSensor_CB_tab           tTouchSensor_INIB_tab
#define tTouchSensor_SINGLE_CELL_CB   tTouchSensor_SINGLE_CELL_INIB
#define tTouchSensor_CB               tTouchSensor_INIB
#define tag_tTouchSensor_CB           tag_tTouchSensor_INIB

extern tTouchSensor_CB  tTouchSensor_CB_tab[];

/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sTouchSensor */
bool_t       tTouchSensor_eTouchSensor_isPressed(tTouchSensor_IDX idx);
void         tTouchSensor_eTouchSensor_initializePort(tTouchSensor_IDX idx);

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

/* IDXの正当性チェックマクロ（短縮形） #_CVIA_# */
#define VALID_IDX(IDX)  tTouchSensor_VALID_IDX(IDX)


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tTouchSensor_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tTouchSensor_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tTouchSensor_IDX


/* 属性アクセスマクロ(短縮形) #_AAMA_# */
#define ATTR_port            tTouchSensor_ATTR_port( p_cellcb )



/* 受け口関数マクロ（短縮形） #_EPM_# */
#define eTouchSensor_isPressed tTouchSensor_eTouchSensor_isPressed
#define eTouchSensor_initializePort tTouchSensor_eTouchSensor_initializePort

/* イテレータコード (FOREACH_CELL)の生成 #_FEC_# */
#define FOREACH_CELL(i,p_cb)   \
    for( (i) = 0; (i) < tTouchSensor_N_CELL; (i)++ ){ \
       //(p_cb) = &tTouchSensor_CB_tab[i];

#define END_FOREACH_CELL   }

/* CB 初期化マクロ #_CIM_# */
#define INITIALIZE_CB(p_that)
#define SET_CB_INIB_POINTER(i,p_that)\
	/* empty */
#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* tTouchSensor_TECSGEN_H */
