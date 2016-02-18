/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef sInitializeRoutineBody_TECSGEN_H
#define sInitializeRoutineBody_TECSGEN_H

/*
 * signature   :  sInitializeRoutineBody
 * global name :  sInitializeRoutineBody
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_sInitializeRoutineBody_VDES {
    struct tag_sInitializeRoutineBody_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_sInitializeRoutineBody_VMT {
    void           (*main__T)( const struct tag_sInitializeRoutineBody_VDES *edp );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_sInitializeRoutineBody_VDES *vdes; } Descriptor( sInitializeRoutineBody );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_SINITIALIZEROUTINEBODY_MAIN     (1)

#endif /* sInitializeRoutineBody_TECSGEN_H */
