/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tBalancer_TECSGEN_H
#define tBalancer_TECSGEN_H

/*
 * celltype          :  tBalancer
 * global name       :  tBalancer
 * idx_is_id(actual) :  no(no)
 * singleton         :  yes
 * has_CB            :  false
 * has_INIB          :  false
 * rom               :  yes
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sBalancer_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* セルタイプのIDX型 #_CTIX_# */
typedef int   tBalancer_IDX;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY


/* セルCBを得るマクロ #_GCB_# */
#define tBalancer_GET_CELLCB(idx) ((void *)0)
#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル CB (ダミー)型宣言 #_CCDP_# */
typedef struct tag_tBalancer_CB {
    int  dummy;
} tBalancer_CB;
/* シングルトンセル CB プロトタイプ宣言 #_SCP_# */


/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sBalancer */
void         tBalancer_eBalancer_control( float32_t forward, float32_t turn, float32_t gyro, float32_t gyroOffset, float32_t leftRevolution, float32_t rightRevolution, float32_t battery, int8_t* pwm_l, int8_t* pwm_r);
void         tBalancer_eBalancer_init();

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tBalancer_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tBalancer_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tBalancer_IDX


/* 受け口関数マクロ（短縮形） #_EPM_# */
#define eBalancer_control tBalancer_eBalancer_control
#define eBalancer_init   tBalancer_eBalancer_init

/* CB 初期化マクロ #_CIM_# */
#define INITIALIZE_CB()
#define SET_CB_INIB_POINTER(i,p_that)\
	/* empty */
#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* tBalancer_TECSGEN_H */
