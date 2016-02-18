/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef sTerminateRoutineBody_TECSGEN_H
#define sTerminateRoutineBody_TECSGEN_H

/*
 * signature   :  sTerminateRoutineBody
 * global name :  sTerminateRoutineBody
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_sTerminateRoutineBody_VDES {
    struct tag_sTerminateRoutineBody_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_sTerminateRoutineBody_VMT {
    void           (*main__T)( const struct tag_sTerminateRoutineBody_VDES *edp );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_sTerminateRoutineBody_VDES *vdes; } Descriptor( sTerminateRoutineBody );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_STERMINATEROUTINEBODY_MAIN      (1)

#endif /* sTerminateRoutineBody_TECSGEN_H */
