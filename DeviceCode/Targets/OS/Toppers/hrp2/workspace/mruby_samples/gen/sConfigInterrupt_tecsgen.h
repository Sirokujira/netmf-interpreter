/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef sConfigInterrupt_TECSGEN_H
#define sConfigInterrupt_TECSGEN_H

/*
 * signature   :  sConfigInterrupt
 * global name :  sConfigInterrupt
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_sConfigInterrupt_VDES {
    struct tag_sConfigInterrupt_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_sConfigInterrupt_VMT {
    ER             (*disable__T)( const struct tag_sConfigInterrupt_VDES *edp );
    ER             (*enable__T)( const struct tag_sConfigInterrupt_VDES *edp );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_sConfigInterrupt_VDES *vdes; } Descriptor( sConfigInterrupt );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_SCONFIGINTERRUPT_DISABLE        (1)
#define	FUNCID_SCONFIGINTERRUPT_ENABLE         (2)

#endif /* sConfigInterrupt_TECSGEN_H */
