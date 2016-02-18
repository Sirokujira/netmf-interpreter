/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef siTask_TECSGEN_H
#define siTask_TECSGEN_H

/*
 * signature   :  siTask
 * global name :  siTask
 * context     :  non-task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_siTask_VDES {
    struct tag_siTask_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_siTask_VMT {
    ER             (*activate__T)( const struct tag_siTask_VDES *edp );
    ER             (*wakeup__T)( const struct tag_siTask_VDES *edp );
    ER             (*releaseWait__T)( const struct tag_siTask_VDES *edp );
    ER             (*raiseException__T)( const struct tag_siTask_VDES *edp, TEXPTN pattern );
    ER             (*disableWait__T)( const struct tag_siTask_VDES *edp );
    ER             (*enableWait__T)( const struct tag_siTask_VDES *edp );
    ER             (*startOverRunHandler__T)( const struct tag_siTask_VDES *edp, OVRTIM ovrtim );
    ER             (*stopOverRunHandler__T)( const struct tag_siTask_VDES *edp );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_siTask_VDES *vdes; } Descriptor( siTask );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_SITASK_ACTIVATE                 (1)
#define	FUNCID_SITASK_WAKEUP                   (2)
#define	FUNCID_SITASK_RELEASEWAIT              (3)
#define	FUNCID_SITASK_RAISEEXCEPTION           (4)
#define	FUNCID_SITASK_DISABLEWAIT              (5)
#define	FUNCID_SITASK_ENABLEWAIT               (6)
#define	FUNCID_SITASK_STARTOVERRUNHANDLER      (7)
#define	FUNCID_SITASK_STOPOVERRUNHANDLER       (8)

#endif /* siTask_TECSGEN_H */
