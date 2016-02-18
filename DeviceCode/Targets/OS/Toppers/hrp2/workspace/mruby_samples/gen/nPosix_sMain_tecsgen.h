/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef nPosix_sMain_TECSGEN_H
#define nPosix_sMain_TECSGEN_H

/*
 * signature   :  sMain
 * global name :  nPosix_sMain
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_nPosix_sMain_VDES {
    struct tag_nPosix_sMain_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_nPosix_sMain_VMT {
    int            (*main__T)( const struct tag_nPosix_sMain_VDES *edp, int argc, const char** argv );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_nPosix_sMain_VDES *vdes; } Descriptor( nPosix_sMain );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_NPOSIX_SMAIN_MAIN               (1)

#endif /* nPosix_sMain_TECSGEN_H */
