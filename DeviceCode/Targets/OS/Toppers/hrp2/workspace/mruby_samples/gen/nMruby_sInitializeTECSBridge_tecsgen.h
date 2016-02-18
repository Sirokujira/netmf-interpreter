/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef nMruby_sInitializeTECSBridge_TECSGEN_H
#define nMruby_sInitializeTECSBridge_TECSGEN_H

/*
 * signature   :  sInitializeTECSBridge
 * global name :  nMruby_sInitializeTECSBridge
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_nMruby_sInitializeTECSBridge_VDES {
    struct tag_nMruby_sInitializeTECSBridge_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_nMruby_sInitializeTECSBridge_VMT {
    void           (*initializeBridge__T)( const struct tag_nMruby_sInitializeTECSBridge_VDES *edp, mrb_state* mrb, struct RClass * TECS );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_nMruby_sInitializeTECSBridge_VDES *vdes; } Descriptor( nMruby_sInitializeTECSBridge );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_NMRUBY_SINITIALIZETECSBRIDGE_INITIALIZEBRIDGE (1)

#endif /* nMruby_sInitializeTECSBridge_TECSGEN_H */
