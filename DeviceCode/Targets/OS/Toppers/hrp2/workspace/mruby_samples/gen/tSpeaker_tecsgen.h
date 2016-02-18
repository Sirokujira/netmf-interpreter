/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tSpeaker_TECSGEN_H
#define tSpeaker_TECSGEN_H

/*
 * celltype          :  tSpeaker
 * global name       :  tSpeaker
 * idx_is_id(actual) :  no(no)
 * singleton         :  yes
 * has_CB            :  false
 * has_INIB          :  false
 * rom               :  yes
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sSpeaker_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* セルタイプのIDX型 #_CTIX_# */
typedef int   tSpeaker_IDX;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY


/* セルCBを得るマクロ #_GCB_# */
#define tSpeaker_GET_CELLCB(idx) ((void *)0)
#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル CB (ダミー)型宣言 #_CCDP_# */
typedef struct tag_tSpeaker_CB {
    int  dummy;
} tSpeaker_CB;
/* シングルトンセル CB プロトタイプ宣言 #_SCP_# */


/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sSpeaker */
ER           tSpeaker_eSpeaker_setVolume( uint8_t volume);
ER           tSpeaker_eSpeaker_playTone( uint16_t frequency, int32_t duration);
ER           tSpeaker_eSpeaker_stop();

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tSpeaker_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tSpeaker_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tSpeaker_IDX


/* 受け口関数マクロ（短縮形） #_EPM_# */
#define eSpeaker_setVolume tSpeaker_eSpeaker_setVolume
#define eSpeaker_playTone tSpeaker_eSpeaker_playTone
#define eSpeaker_stop    tSpeaker_eSpeaker_stop

/* CB 初期化マクロ #_CIM_# */
#define INITIALIZE_CB()
#define SET_CB_INIB_POINTER(i,p_that)\
	/* empty */
#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* tSpeaker_TECSGEN_H */
