/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tEV3Platform_TECSGEN_H
#define tEV3Platform_TECSGEN_H

/*
 * celltype          :  tEV3Platform
 * global name       :  tEV3Platform
 * idx_is_id(actual) :  no(no)
 * singleton         :  no
 * has_CB            :  false
 * has_INIB          :  false
 * rom               :  yes
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sTaskBody_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* セルタイプのIDX型 #_CTIX_# */
typedef int   tEV3Platform_IDX;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

#define tEV3Platform_ID_BASE        (1)  /* ID のベース  #_NIDB_# */
#define tEV3Platform_N_CELL         (1)  /* セルの個数  #_NCEL_# */

/* IDXの正当性チェックマクロ #_CVI_# */
#define tEV3Platform_VALID_IDX(IDX) (1)


/* セルCBを得るマクロ #_GCB_# */
#define tEV3Platform_GET_CELLCB(idx) ((void *)0)
#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル CB (ダミー)型宣言 #_CCDP_# */
typedef struct tag_tEV3Platform_CB {
    int  dummy;
} tEV3Platform_CB;
extern tEV3Platform_CB  tEV3Platform_CB_tab[];

/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sTaskBody */
void         tEV3Platform_eTaskBody_main(tEV3Platform_IDX idx);

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */
/* eTaskBody */
void           tEV3Platform_eTaskBody_main_skel( const struct tag_sTaskBody_VDES *epd);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

/* IDXの正当性チェックマクロ（短縮形） #_CVIA_# */
#define VALID_IDX(IDX)  tEV3Platform_VALID_IDX(IDX)


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tEV3Platform_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tEV3Platform_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tEV3Platform_IDX


/* 受け口関数マクロ（短縮形） #_EPM_# */
#define eTaskBody_main   tEV3Platform_eTaskBody_main

/* イテレータコード (FOREACH_CELL)の生成(CB,INIB は存在しない) #_NFEC_# */
#define FOREACH_CELL(i,p_cb)   \
    for((i)=0;(i)<0;(i)++){

#define END_FOREACH_CELL   }

/* CB 初期化マクロ #_CIM_# */
#define INITIALIZE_CB(p_that)
#define SET_CB_INIB_POINTER(i,p_that)\
	/* empty */
#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* tEV3Platform_TECSGEN_H */
