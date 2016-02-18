/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef nMruby_tsLCD_TECSGEN_H
#define nMruby_tsLCD_TECSGEN_H

/*
 * celltype          :  tsLCD
 * global name       :  nMruby_tsLCD
 * idx_is_id(actual) :  yes(no)
 * singleton         :  no
 * has_CB            :  false
 * has_INIB          :  false
 * rom               :  yes
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sLCD_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* セルタイプのIDX型 #_CTIX_# */
typedef int   nMruby_tsLCD_IDX;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* 最適化のため参照するセルタイプの CB 型の定義を取込む #_ICT_# */
#ifndef  TOPPERS_CB_TYPE_ONLY
#define  nMruby_tsLCD_CB_TYPE_ONLY
#define TOPPERS_CB_TYPE_ONLY
#endif  /* TOPPERS_CB_TYPE_ONLY */
#include "tLCD_tecsgen.h"
#ifdef  nMruby_tsLCD_CB_TYPE_ONLY
#undef TOPPERS_CB_TYPE_ONLY
#endif /* nMruby_tsLCD_CB_TYPE_ONLY */
#ifndef TOPPERS_CB_TYPE_ONLY

#define nMruby_tsLCD_ID_BASE        (1)  /* ID のベース  #_NIDB_# */
#define nMruby_tsLCD_N_CELL         (1)  /* セルの個数  #_NCEL_# */

/* IDXの正当性チェックマクロ #_CVI_# */
#define nMruby_tsLCD_VALID_IDX(IDX) (1)


/* セルCBを得るマクロ #_GCB_# */
#define nMruby_tsLCD_GET_CELLCB(idx) ((void *)0)
 /* 呼び口関数マクロ #_CPM_# */
#define nMruby_tsLCD_cTECS_setFont( p_that, font ) \
	  tLCD_eLCD_setFont( \
	   &tLCD_CB_tab[0], (font) )
#define nMruby_tsLCD_cTECS_getFontSize( p_that, font, p_width, p_height ) \
	  tLCD_eLCD_getFontSize( \
	   &tLCD_CB_tab[0], (font), (p_width), (p_height) )
#define nMruby_tsLCD_cTECS_drawString( p_that, str, x, y ) \
	  tLCD_eLCD_drawString( \
	   &tLCD_CB_tab[0], (str), (x), (y) )
#define nMruby_tsLCD_cTECS_fillRect( p_that, x, y, w, h, color ) \
	  tLCD_eLCD_fillRect( \
	   &tLCD_CB_tab[0], (x), (y), (w), (h), (color) )
#define nMruby_tsLCD_cTECS_drawLine( p_that, x0, y0, x1, y1 ) \
	  tLCD_eLCD_drawLine( \
	   &tLCD_CB_tab[0], (x0), (y0), (x1), (y1) )
#define nMruby_tsLCD_cTECS_print( p_that, str ) \
	  tLCD_eLCD_print( \
	   &tLCD_CB_tab[0], (str) )
#define nMruby_tsLCD_cTECS_puts( p_that, str ) \
	  tLCD_eLCD_puts( \
	   &tLCD_CB_tab[0], (str) )
#define nMruby_tsLCD_cTECS_clear( p_that ) \
	  tLCD_eLCD_clear( \
	   &tLCD_CB_tab[0] )
#define nMruby_tsLCD_cTECS_showMessageBox( p_that, title, msg ) \
	  tLCD_eLCD_showMessageBox( \
	   &tLCD_CB_tab[0], (title), (msg) )

#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル CB (ダミー)型宣言 #_CCDP_# */
typedef struct tag_nMruby_tsLCD_CB {
    int  dummy;
} nMruby_tsLCD_CB;
extern nMruby_tsLCD_CB  nMruby_tsLCD_CB_tab[];

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

/* IDXの正当性チェックマクロ（短縮形） #_CVIA_# */
#define VALID_IDX(IDX)  nMruby_tsLCD_VALID_IDX(IDX)


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  nMruby_tsLCD_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	nMruby_tsLCD_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	nMruby_tsLCD_IDX

#define tsLCD_IDX  nMruby_tsLCD_IDX
/* 呼び口関数マクロ（短縮形）#_CPMA_# */
#define cTECS_setFont( font ) \
                      nMruby_tsLCD_cTECS_setFont( p_cellcb, font ) 
#define cTECS_getFontSize( font, p_width, p_height ) \
                      nMruby_tsLCD_cTECS_getFontSize( p_cellcb, font, p_width, p_height ) 
#define cTECS_drawString( str, x, y ) \
                      nMruby_tsLCD_cTECS_drawString( p_cellcb, str, x, y ) 
#define cTECS_fillRect( x, y, w, h, color ) \
                      nMruby_tsLCD_cTECS_fillRect( p_cellcb, x, y, w, h, color ) 
#define cTECS_drawLine( x0, y0, x1, y1 ) \
                      nMruby_tsLCD_cTECS_drawLine( p_cellcb, x0, y0, x1, y1 ) 
#define cTECS_print( str ) \
                      nMruby_tsLCD_cTECS_print( p_cellcb, str ) 
#define cTECS_puts( str ) \
                      nMruby_tsLCD_cTECS_puts( p_cellcb, str ) 
#define cTECS_clear( ) \
                      nMruby_tsLCD_cTECS_clear( p_cellcb ) 
#define cTECS_showMessageBox( title, msg ) \
                      nMruby_tsLCD_cTECS_showMessageBox( p_cellcb, title, msg ) 

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

#endif /* nMruby_tsLCD_TECSGEN_H */
