/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef sButton_TECSGEN_H
#define sButton_TECSGEN_H

/*
 * signature   :  sButton
 * global name :  sButton
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_sButton_VDES {
    struct tag_sButton_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_sButton_VMT {
    bool_t         (*isPressed__T)( const struct tag_sButton_VDES *edp, button_t button );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_sButton_VDES *vdes; } Descriptor( sButton );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_SBUTTON_ISPRESSED               (1)

#endif /* sButton_TECSGEN_H */
