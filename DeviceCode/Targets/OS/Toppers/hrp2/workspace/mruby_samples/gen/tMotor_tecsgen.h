/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tMotor_TECSGEN_H
#define tMotor_TECSGEN_H

/*
 * celltype          :  tMotor
 * global name       :  tMotor
 * idx_is_id(actual) :  no(no)
 * singleton         :  no
 * has_CB            :  false
 * has_INIB          :  true
 * rom               :  yes
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sMotor_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* セルタイプのIDX型 #_CTIX_# */
typedef const struct tag_tMotor_INIB *tMotor_IDX;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

#define tMotor_ID_BASE              (1)  /* ID のベース  #_NIDB_# */
#define tMotor_N_CELL               (4)  /* セルの個数  #_NCEL_# */

/* IDXの正当性チェックマクロ #_CVI_# */
#define tMotor_VALID_IDX(IDX) (1)


/* セルCBを得るマクロ #_GCB_# */
#define tMotor_GET_CELLCB(idx) (idx)

/* 属性アクセスマクロ #_AAM_# */
#define tMotor_ATTR_port( p_that )	((p_that)->port)

#define tMotor_GET_port(p_that)	((p_that)->port)



#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル INIB 型宣言 #_CIP_# */
typedef const struct tag_tMotor_INIB {
    /* call port #_NEP_# */ 
    /* attribute(RO) #_ATO_# */ 
    int32_t        port;
}  tMotor_INIB;

/* CB は存在しない。INIB を CB の代わりに使用するための define #_DCI_# */
#define tMotor_CB_tab           tMotor_INIB_tab
#define tMotor_SINGLE_CELL_CB   tMotor_SINGLE_CELL_INIB
#define tMotor_CB               tMotor_INIB
#define tag_tMotor_CB           tag_tMotor_INIB

extern tMotor_CB  tMotor_CB_tab[];

/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sMotor */
ER_UINT      tMotor_eMotor_getType(tMotor_IDX idx);
int32_t      tMotor_eMotor_getCounts(tMotor_IDX idx);
int          tMotor_eMotor_getPower(tMotor_IDX idx);
ER           tMotor_eMotor_resetCounts(tMotor_IDX idx);
ER           tMotor_eMotor_setPower(tMotor_IDX idx, int power);
ER           tMotor_eMotor_stop(tMotor_IDX idx, bool_t brake);
ER           tMotor_eMotor_rotate(tMotor_IDX idx, int degrees, uint32_t speed_abs, bool_t blocking);
void         tMotor_eMotor_initializePort(tMotor_IDX idx, int32_t type);

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

/* IDXの正当性チェックマクロ（短縮形） #_CVIA_# */
#define VALID_IDX(IDX)  tMotor_VALID_IDX(IDX)


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tMotor_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tMotor_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tMotor_IDX


/* 属性アクセスマクロ(短縮形) #_AAMA_# */
#define ATTR_port            tMotor_ATTR_port( p_cellcb )



/* 受け口関数マクロ（短縮形） #_EPM_# */
#define eMotor_getType   tMotor_eMotor_getType
#define eMotor_getCounts tMotor_eMotor_getCounts
#define eMotor_getPower  tMotor_eMotor_getPower
#define eMotor_resetCounts tMotor_eMotor_resetCounts
#define eMotor_setPower  tMotor_eMotor_setPower
#define eMotor_stop      tMotor_eMotor_stop
#define eMotor_rotate    tMotor_eMotor_rotate
#define eMotor_initializePort tMotor_eMotor_initializePort

/* イテレータコード (FOREACH_CELL)の生成 #_FEC_# */
#define FOREACH_CELL(i,p_cb)   \
    for( (i) = 0; (i) < tMotor_N_CELL; (i)++ ){ \
       //(p_cb) = &tMotor_CB_tab[i];

#define END_FOREACH_CELL   }

/* CB 初期化マクロ #_CIM_# */
#define INITIALIZE_CB(p_that)
#define SET_CB_INIB_POINTER(i,p_that)\
	/* empty */
#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* tMotor_TECSGEN_H */
