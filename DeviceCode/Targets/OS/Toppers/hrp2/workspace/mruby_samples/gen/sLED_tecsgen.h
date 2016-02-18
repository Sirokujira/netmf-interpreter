/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef sLED_TECSGEN_H
#define sLED_TECSGEN_H

/*
 * signature   :  sLED
 * global name :  sLED
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_sLED_VDES {
    struct tag_sLED_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_sLED_VMT {
    ER             (*setColor__T)( const struct tag_sLED_VDES *edp, ledcolor_t color );
    ER             (*off__T)( const struct tag_sLED_VDES *edp );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_sLED_VDES *vdes; } Descriptor( sLED );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_SLED_SETCOLOR                   (1)
#define	FUNCID_SLED_OFF                        (2)

#endif /* sLED_TECSGEN_H */
