/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef sLCD_TECSGEN_H
#define sLCD_TECSGEN_H

/*
 * signature   :  sLCD
 * global name :  sLCD
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_sLCD_VDES {
    struct tag_sLCD_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_sLCD_VMT {
    ER             (*setFont__T)( const struct tag_sLCD_VDES *edp, lcdfont_t font );
    ER             (*getFontSize__T)( const struct tag_sLCD_VDES *edp, lcdfont_t font, int32_t* p_width, int32_t* p_height );
    ER             (*drawString__T)( const struct tag_sLCD_VDES *edp, const char* str, int32_t x, int32_t y );
    ER             (*fillRect__T)( const struct tag_sLCD_VDES *edp, int32_t x, int32_t y, int32_t w, int32_t h, lcdcolor_t color );
    ER             (*drawLine__T)( const struct tag_sLCD_VDES *edp, int32_t x0, int32_t y0, int32_t x1, int32_t y1 );
    void           (*print__T)( const struct tag_sLCD_VDES *edp, const char* str );
    void           (*puts__T)( const struct tag_sLCD_VDES *edp, const char* str );
    void           (*clear__T)( const struct tag_sLCD_VDES *edp );
    void           (*showMessageBox__T)( const struct tag_sLCD_VDES *edp, const char* title, const char* msg );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_sLCD_VDES *vdes; } Descriptor( sLCD );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_SLCD_SETFONT                    (1)
#define	FUNCID_SLCD_GETFONTSIZE                (2)
#define	FUNCID_SLCD_DRAWSTRING                 (3)
#define	FUNCID_SLCD_FILLRECT                   (4)
#define	FUNCID_SLCD_DRAWLINE                   (5)
#define	FUNCID_SLCD_PRINT                      (6)
#define	FUNCID_SLCD_PUTS                       (7)
#define	FUNCID_SLCD_CLEAR                      (8)
#define	FUNCID_SLCD_SHOWMESSAGEBOX             (9)

#endif /* sLCD_TECSGEN_H */
