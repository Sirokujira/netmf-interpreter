/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef sKernel_TECSGEN_H
#define sKernel_TECSGEN_H

/*
 * signature   :  sKernel
 * global name :  sKernel
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_sKernel_VDES {
    struct tag_sKernel_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_sKernel_VMT {
    ER             (*sleep__T)( const struct tag_sKernel_VDES *edp );
    ER             (*sleepTimeout__T)( const struct tag_sKernel_VDES *edp, TMO timeout );
    ER             (*delay__T)( const struct tag_sKernel_VDES *edp, RELTIM delayTime );
    ER             (*exitTask__T)( const struct tag_sKernel_VDES *edp );
    ER             (*getTaskId__T)( const struct tag_sKernel_VDES *edp, ID* p_taskId );
    ER             (*rotateReadyQueue__T)( const struct tag_sKernel_VDES *edp, PRI taskPriority );
    ER             (*getTime__T)( const struct tag_sKernel_VDES *edp, SYSTIM* p_systemTime );
    ER             (*getMicroTime__T)( const struct tag_sKernel_VDES *edp, SYSUTM* p_systemMicroTime );
    ER             (*lockCpu__T)( const struct tag_sKernel_VDES *edp );
    ER             (*unlockCpu__T)( const struct tag_sKernel_VDES *edp );
    ER             (*disableDispatch__T)( const struct tag_sKernel_VDES *edp );
    ER             (*enableDispatch__T)( const struct tag_sKernel_VDES *edp );
    ER             (*disableTaskException__T)( const struct tag_sKernel_VDES *edp );
    ER             (*enableTaskException__T)( const struct tag_sKernel_VDES *edp );
    ER             (*changeInterruptPriorityMask__T)( const struct tag_sKernel_VDES *edp, PRI interruptPriority );
    ER             (*getInterruptPriorityMask__T)( const struct tag_sKernel_VDES *edp, PRI* p_interruptPriority );
    ER             (*exitKernel__T)( const struct tag_sKernel_VDES *edp );
    bool_t         (*senseContext__T)( const struct tag_sKernel_VDES *edp );
    bool_t         (*senseLock__T)( const struct tag_sKernel_VDES *edp );
    bool_t         (*senseDispatch__T)( const struct tag_sKernel_VDES *edp );
    bool_t         (*senseDispatchPendingState__T)( const struct tag_sKernel_VDES *edp );
    bool_t         (*senseKernel__T)( const struct tag_sKernel_VDES *edp );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_sKernel_VDES *vdes; } Descriptor( sKernel );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_SKERNEL_SLEEP                   (1)
#define	FUNCID_SKERNEL_SLEEPTIMEOUT            (2)
#define	FUNCID_SKERNEL_DELAY                   (3)
#define	FUNCID_SKERNEL_EXITTASK                (4)
#define	FUNCID_SKERNEL_GETTASKID               (5)
#define	FUNCID_SKERNEL_ROTATEREADYQUEUE        (6)
#define	FUNCID_SKERNEL_GETTIME                 (7)
#define	FUNCID_SKERNEL_GETMICROTIME            (8)
#define	FUNCID_SKERNEL_LOCKCPU                 (9)
#define	FUNCID_SKERNEL_UNLOCKCPU               (10)
#define	FUNCID_SKERNEL_DISABLEDISPATCH         (11)
#define	FUNCID_SKERNEL_ENABLEDISPATCH          (12)
#define	FUNCID_SKERNEL_DISABLETASKEXCEPTION    (13)
#define	FUNCID_SKERNEL_ENABLETASKEXCEPTION     (14)
#define	FUNCID_SKERNEL_CHANGEINTERRUPTPRIORITYMASK (15)
#define	FUNCID_SKERNEL_GETINTERRUPTPRIORITYMASK (16)
#define	FUNCID_SKERNEL_EXITKERNEL              (17)
#define	FUNCID_SKERNEL_SENSECONTEXT            (18)
#define	FUNCID_SKERNEL_SENSELOCK               (19)
#define	FUNCID_SKERNEL_SENSEDISPATCH           (20)
#define	FUNCID_SKERNEL_SENSEDISPATCHPENDINGSTATE (21)
#define	FUNCID_SKERNEL_SENSEKERNEL             (22)

#endif /* sKernel_TECSGEN_H */
