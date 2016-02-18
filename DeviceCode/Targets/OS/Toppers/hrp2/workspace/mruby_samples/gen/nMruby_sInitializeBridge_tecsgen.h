/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef nMruby_sInitializeBridge_TECSGEN_H
#define nMruby_sInitializeBridge_TECSGEN_H

/*
 * signature   :  sInitializeBridge
 * global name :  nMruby_sInitializeBridge
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_nMruby_sInitializeBridge_VDES {
    struct tag_nMruby_sInitializeBridge_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_nMruby_sInitializeBridge_VMT {
    void           (*initializeBridge__T)( const struct tag_nMruby_sInitializeBridge_VDES *edp, const mrb_state* mrb );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_nMruby_sInitializeBridge_VDES *vdes; } Descriptor( nMruby_sInitializeBridge );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_NMRUBY_SINITIALIZEBRIDGE_INITIALIZEBRIDGE (1)

#endif /* nMruby_sInitializeBridge_TECSGEN_H */
