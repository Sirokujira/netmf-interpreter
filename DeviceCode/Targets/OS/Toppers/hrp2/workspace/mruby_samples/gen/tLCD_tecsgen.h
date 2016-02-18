/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tLCD_TECSGEN_H
#define tLCD_TECSGEN_H

/*
 * celltype          :  tLCD
 * global name       :  tLCD
 * idx_is_id(actual) :  no(no)
 * singleton         :  no
 * has_CB            :  true
 * has_INIB          :  false
 * rom               :  yes
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sLCD_tecsgen.h"
#include "sButton_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* セルタイプのIDX型 #_CTIX_# */
typedef struct tag_tLCD_CB *tLCD_IDX;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* 最適化のため参照するセルタイプの CB 型の定義を取込む #_ICT_# */
#ifndef  TOPPERS_CB_TYPE_ONLY
#define  tLCD_CB_TYPE_ONLY
#define TOPPERS_CB_TYPE_ONLY
#endif  /* TOPPERS_CB_TYPE_ONLY */
#include "tButton_tecsgen.h"
#ifdef  tLCD_CB_TYPE_ONLY
#undef TOPPERS_CB_TYPE_ONLY
#endif /* tLCD_CB_TYPE_ONLY */
#ifndef TOPPERS_CB_TYPE_ONLY

#define tLCD_ID_BASE                (1)  /* ID のベース  #_NIDB_# */
#define tLCD_N_CELL                 (1)  /* セルの個数  #_NCEL_# */

/* IDXの正当性チェックマクロ #_CVI_# */
#define tLCD_VALID_IDX(IDX) (1)


/* セルCBを得るマクロ #_GCB_# */
#define tLCD_GET_CELLCB(idx) (idx)



/* var アクセスマクロ #_VAM_# */
#define tLCD_VAR_currentFont(p_that)	((p_that)->currentFont)

#define tLCD_GET_currentFont(p_that)	((p_that)->currentFont)
#define tLCD_SET_currentFont(p_that,val)	((p_that)->currentFont=(val))

 /* 呼び口関数マクロ #_CPM_# */
#define tLCD_cButton_isPressed( p_that, button ) \
	  tButton_eButton_isPressed( \
	   (tButton_IDX)0, (button) )

#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル CB 型宣言 #_CCTPA_# */
typedef struct tag_tLCD_CB {
    /* var #_VA_# */ 
    lcdfont_t      currentFont;
}  tLCD_CB;
extern tLCD_CB  tLCD_CB_tab[];

/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sLCD */
ER           tLCD_eLCD_setFont(tLCD_IDX idx, lcdfont_t font);
ER           tLCD_eLCD_getFontSize(tLCD_IDX idx, lcdfont_t font, int32_t* p_width, int32_t* p_height);
ER           tLCD_eLCD_drawString(tLCD_IDX idx, const char* str, int32_t x, int32_t y);
ER           tLCD_eLCD_fillRect(tLCD_IDX idx, int32_t x, int32_t y, int32_t w, int32_t h, lcdcolor_t color);
ER           tLCD_eLCD_drawLine(tLCD_IDX idx, int32_t x0, int32_t y0, int32_t x1, int32_t y1);
void         tLCD_eLCD_print(tLCD_IDX idx, const char* str);
void         tLCD_eLCD_puts(tLCD_IDX idx, const char* str);
void         tLCD_eLCD_clear(tLCD_IDX idx);
void         tLCD_eLCD_showMessageBox(tLCD_IDX idx, const char* title, const char* msg);

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

/* IDXの正当性チェックマクロ（短縮形） #_CVIA_# */
#define VALID_IDX(IDX)  tLCD_VALID_IDX(IDX)


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tLCD_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tLCD_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tLCD_IDX



/* var アクセスマクロ(短縮形) #_VAMA_# */
#define VAR_currentFont      tLCD_VAR_currentFont( p_cellcb )

/* 呼び口関数マクロ（短縮形）#_CPMA_# */
#define cButton_isPressed( button ) \
                      tLCD_cButton_isPressed( p_cellcb, button ) 


/* 受け口関数マクロ（短縮形） #_EPM_# */
#define eLCD_setFont     tLCD_eLCD_setFont
#define eLCD_getFontSize tLCD_eLCD_getFontSize
#define eLCD_drawString  tLCD_eLCD_drawString
#define eLCD_fillRect    tLCD_eLCD_fillRect
#define eLCD_drawLine    tLCD_eLCD_drawLine
#define eLCD_print       tLCD_eLCD_print
#define eLCD_puts        tLCD_eLCD_puts
#define eLCD_clear       tLCD_eLCD_clear
#define eLCD_showMessageBox tLCD_eLCD_showMessageBox

/* イテレータコード (FOREACH_CELL)の生成 #_FEC_# */
#define FOREACH_CELL(i,p_cb)   \
    for( (i) = 0; (i) < tLCD_N_CELL; (i)++ ){ \
       (p_cb) = &tLCD_CB_tab[i];

#define END_FOREACH_CELL   }

/* CB 初期化マクロ #_CIM_# */
#define INITIALIZE_CB(p_that)
#define SET_CB_INIB_POINTER(i,p_that)\
	/* empty */
#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* tLCD_TECSGEN_H */
