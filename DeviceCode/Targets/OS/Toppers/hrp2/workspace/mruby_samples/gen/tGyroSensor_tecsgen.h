/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tGyroSensor_TECSGEN_H
#define tGyroSensor_TECSGEN_H

/*
 * celltype          :  tGyroSensor
 * global name       :  tGyroSensor
 * idx_is_id(actual) :  no(no)
 * singleton         :  no
 * has_CB            :  false
 * has_INIB          :  true
 * rom               :  yes
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sGyroSensor_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* セルタイプのIDX型 #_CTIX_# */
typedef const struct tag_tGyroSensor_INIB *tGyroSensor_IDX;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

#define tGyroSensor_ID_BASE         (1)  /* ID のベース  #_NIDB_# */
#define tGyroSensor_N_CELL          (4)  /* セルの個数  #_NCEL_# */

/* IDXの正当性チェックマクロ #_CVI_# */
#define tGyroSensor_VALID_IDX(IDX) (1)


/* セルCBを得るマクロ #_GCB_# */
#define tGyroSensor_GET_CELLCB(idx) (idx)

/* 属性アクセスマクロ #_AAM_# */
#define tGyroSensor_ATTR_port( p_that )	((p_that)->port)

#define tGyroSensor_GET_port(p_that)	((p_that)->port)



#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル INIB 型宣言 #_CIP_# */
typedef const struct tag_tGyroSensor_INIB {
    /* call port #_NEP_# */ 
    /* attribute(RO) #_ATO_# */ 
    int32_t        port;
}  tGyroSensor_INIB;

/* CB は存在しない。INIB を CB の代わりに使用するための define #_DCI_# */
#define tGyroSensor_CB_tab           tGyroSensor_INIB_tab
#define tGyroSensor_SINGLE_CELL_CB   tGyroSensor_SINGLE_CELL_INIB
#define tGyroSensor_CB               tGyroSensor_INIB
#define tag_tGyroSensor_CB           tag_tGyroSensor_INIB

extern tGyroSensor_CB  tGyroSensor_CB_tab[];

/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sGyroSensor */
int16_t      tGyroSensor_eGyroSensor_getAngle(tGyroSensor_IDX idx);
int16_t      tGyroSensor_eGyroSensor_getRate(tGyroSensor_IDX idx);
ER           tGyroSensor_eGyroSensor_reset(tGyroSensor_IDX idx);
float32_t    tGyroSensor_eGyroSensor_calibrate(tGyroSensor_IDX idx, int32_t times);
void         tGyroSensor_eGyroSensor_initializePort(tGyroSensor_IDX idx);

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

/* IDXの正当性チェックマクロ（短縮形） #_CVIA_# */
#define VALID_IDX(IDX)  tGyroSensor_VALID_IDX(IDX)


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tGyroSensor_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tGyroSensor_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tGyroSensor_IDX


/* 属性アクセスマクロ(短縮形) #_AAMA_# */
#define ATTR_port            tGyroSensor_ATTR_port( p_cellcb )



/* 受け口関数マクロ（短縮形） #_EPM_# */
#define eGyroSensor_getAngle tGyroSensor_eGyroSensor_getAngle
#define eGyroSensor_getRate tGyroSensor_eGyroSensor_getRate
#define eGyroSensor_reset tGyroSensor_eGyroSensor_reset
#define eGyroSensor_calibrate tGyroSensor_eGyroSensor_calibrate
#define eGyroSensor_initializePort tGyroSensor_eGyroSensor_initializePort

/* イテレータコード (FOREACH_CELL)の生成 #_FEC_# */
#define FOREACH_CELL(i,p_cb)   \
    for( (i) = 0; (i) < tGyroSensor_N_CELL; (i)++ ){ \
       //(p_cb) = &tGyroSensor_CB_tab[i];

#define END_FOREACH_CELL   }

/* CB 初期化マクロ #_CIM_# */
#define INITIALIZE_CB(p_that)
#define SET_CB_INIB_POINTER(i,p_that)\
	/* empty */
#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* tGyroSensor_TECSGEN_H */
