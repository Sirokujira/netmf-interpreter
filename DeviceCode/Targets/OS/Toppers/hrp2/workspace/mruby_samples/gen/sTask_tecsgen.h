/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef sTask_TECSGEN_H
#define sTask_TECSGEN_H

/*
 * signature   :  sTask
 * global name :  sTask
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_sTask_VDES {
    struct tag_sTask_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_sTask_VMT {
    ER             (*activate__T)( const struct tag_sTask_VDES *edp );
    ER_UINT        (*cancelActivate__T)( const struct tag_sTask_VDES *edp );
    ER             (*terminate__T)( const struct tag_sTask_VDES *edp );
    ER             (*changePriority__T)( const struct tag_sTask_VDES *edp, PRI priority );
    ER             (*getPriority__T)( const struct tag_sTask_VDES *edp, PRI* p_priority );
    ER             (*refer__T)( const struct tag_sTask_VDES *edp, T_RTSK* pk_taskStatus );
    ER             (*wakeup__T)( const struct tag_sTask_VDES *edp );
    ER_UINT        (*cancelWakeup__T)( const struct tag_sTask_VDES *edp );
    ER             (*releaseWait__T)( const struct tag_sTask_VDES *edp );
    ER             (*suspend__T)( const struct tag_sTask_VDES *edp );
    ER             (*resume__T)( const struct tag_sTask_VDES *edp );
    ER             (*raiseException__T)( const struct tag_sTask_VDES *edp, TEXPTN pattern );
    ER             (*referException__T)( const struct tag_sTask_VDES *edp, T_RTEX* pk_rtex );
    ER             (*startOverRunHandler__T)( const struct tag_sTask_VDES *edp, OVRTIM ovrtim );
    ER             (*stopOverRunHandler__T)( const struct tag_sTask_VDES *edp );
    ER             (*referOverRunHandler__T)( const struct tag_sTask_VDES *edp, T_ROVR* pk_rovr );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_sTask_VDES *vdes; } Descriptor( sTask );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_STASK_ACTIVATE                  (1)
#define	FUNCID_STASK_CANCELACTIVATE            (2)
#define	FUNCID_STASK_TERMINATE                 (3)
#define	FUNCID_STASK_CHANGEPRIORITY            (4)
#define	FUNCID_STASK_GETPRIORITY               (5)
#define	FUNCID_STASK_REFER                     (6)
#define	FUNCID_STASK_WAKEUP                    (7)
#define	FUNCID_STASK_CANCELWAKEUP              (8)
#define	FUNCID_STASK_RELEASEWAIT               (9)
#define	FUNCID_STASK_SUSPEND                   (10)
#define	FUNCID_STASK_RESUME                    (11)
#define	FUNCID_STASK_RAISEEXCEPTION            (12)
#define	FUNCID_STASK_REFEREXCEPTION            (13)
#define	FUNCID_STASK_STARTOVERRUNHANDLER       (14)
#define	FUNCID_STASK_STOPOVERRUNHANDLER        (15)
#define	FUNCID_STASK_REFEROVERRUNHANDLER       (16)

#endif /* sTask_TECSGEN_H */
