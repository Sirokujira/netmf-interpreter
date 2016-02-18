/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tKernel_TECSGEN_H
#define tKernel_TECSGEN_H

/*
 * celltype          :  tKernel
 * global name       :  tKernel
 * idx_is_id(actual) :  no(no)
 * singleton         :  yes
 * has_CB            :  false
 * has_INIB          :  false
 * rom               :  yes
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sKernel_tecsgen.h"
#include "siKernel_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* セルタイプのIDX型 #_CTIX_# */
typedef int   tKernel_IDX;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */


/* セルCBを得るマクロ #_GCB_# */
#define tKernel_GET_CELLCB(idx) ((void *)0)
#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル CB (ダミー)型宣言 #_CCDP_# */
typedef struct tag_tKernel_CB {
    int  dummy;
} tKernel_CB;
/* シングルトンセル CB プロトタイプ宣言 #_SCP_# */


/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sKernel */
Inline ER           tKernel_eKernel_sleep();
Inline ER           tKernel_eKernel_sleepTimeout( TMO timeout);
Inline ER           tKernel_eKernel_delay( RELTIM delayTime);
Inline ER           tKernel_eKernel_exitTask();
Inline ER           tKernel_eKernel_getTaskId( ID* p_taskId);
Inline ER           tKernel_eKernel_rotateReadyQueue( PRI taskPriority);
Inline ER           tKernel_eKernel_getTime( SYSTIM* p_systemTime);
Inline ER           tKernel_eKernel_getMicroTime( SYSUTM* p_systemMicroTime);
Inline ER           tKernel_eKernel_lockCpu();
Inline ER           tKernel_eKernel_unlockCpu();
Inline ER           tKernel_eKernel_disableDispatch();
Inline ER           tKernel_eKernel_enableDispatch();
Inline ER           tKernel_eKernel_disableTaskException();
Inline ER           tKernel_eKernel_enableTaskException();
Inline ER           tKernel_eKernel_changeInterruptPriorityMask( PRI interruptPriority);
Inline ER           tKernel_eKernel_getInterruptPriorityMask( PRI* p_interruptPriority);
Inline ER           tKernel_eKernel_exitKernel();
Inline bool_t       tKernel_eKernel_senseContext();
Inline bool_t       tKernel_eKernel_senseLock();
Inline bool_t       tKernel_eKernel_senseDispatch();
Inline bool_t       tKernel_eKernel_senseDispatchPendingState();
Inline bool_t       tKernel_eKernel_senseKernel();
/* siKernel */
Inline ER           tKernel_eiKernel_getTaskId( ID* p_taskId);
Inline ER           tKernel_eiKernel_rotateReadyQueue( PRI taskPriority);
Inline ER           tKernel_eiKernel_getMicroTime( SYSUTM* p_systemMicroTime);
Inline ER           tKernel_eiKernel_lockCpu();
Inline ER           tKernel_eiKernel_unlockCpu();
Inline ER           tKernel_eiKernel_exitKernel();
Inline bool_t       tKernel_eiKernel_senseContext();
Inline bool_t       tKernel_eiKernel_senseLock();
Inline bool_t       tKernel_eiKernel_senseDispatch();
Inline bool_t       tKernel_eiKernel_senseDispatchPendingState();
Inline bool_t       tKernel_eiKernel_senseKernel();
Inline bool_t       tKernel_eiKernel_senseDispatchPendingStateCPU( const void* p_exceptionInfomation);
Inline bool_t       tKernel_eiKernel_senseTaskExceptionPendingStateCPU( const void* p_exceptionInfomation);

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tKernel_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tKernel_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tKernel_IDX


/* 受け口関数マクロ（短縮形） #_EPM_# */
#define eKernel_sleep    tKernel_eKernel_sleep
#define eKernel_sleepTimeout tKernel_eKernel_sleepTimeout
#define eKernel_delay    tKernel_eKernel_delay
#define eKernel_exitTask tKernel_eKernel_exitTask
#define eKernel_getTaskId tKernel_eKernel_getTaskId
#define eKernel_rotateReadyQueue tKernel_eKernel_rotateReadyQueue
#define eKernel_getTime  tKernel_eKernel_getTime
#define eKernel_getMicroTime tKernel_eKernel_getMicroTime
#define eKernel_lockCpu  tKernel_eKernel_lockCpu
#define eKernel_unlockCpu tKernel_eKernel_unlockCpu
#define eKernel_disableDispatch tKernel_eKernel_disableDispatch
#define eKernel_enableDispatch tKernel_eKernel_enableDispatch
#define eKernel_disableTaskException tKernel_eKernel_disableTaskException
#define eKernel_enableTaskException tKernel_eKernel_enableTaskException
#define eKernel_changeInterruptPriorityMask tKernel_eKernel_changeInterruptPriorityMask
#define eKernel_getInterruptPriorityMask tKernel_eKernel_getInterruptPriorityMask
#define eKernel_exitKernel tKernel_eKernel_exitKernel
#define eKernel_senseContext tKernel_eKernel_senseContext
#define eKernel_senseLock tKernel_eKernel_senseLock
#define eKernel_senseDispatch tKernel_eKernel_senseDispatch
#define eKernel_senseDispatchPendingState tKernel_eKernel_senseDispatchPendingState
#define eKernel_senseKernel tKernel_eKernel_senseKernel
#define eiKernel_getTaskId tKernel_eiKernel_getTaskId
#define eiKernel_rotateReadyQueue tKernel_eiKernel_rotateReadyQueue
#define eiKernel_getMicroTime tKernel_eiKernel_getMicroTime
#define eiKernel_lockCpu tKernel_eiKernel_lockCpu
#define eiKernel_unlockCpu tKernel_eiKernel_unlockCpu
#define eiKernel_exitKernel tKernel_eiKernel_exitKernel
#define eiKernel_senseContext tKernel_eiKernel_senseContext
#define eiKernel_senseLock tKernel_eiKernel_senseLock
#define eiKernel_senseDispatch tKernel_eiKernel_senseDispatch
#define eiKernel_senseDispatchPendingState tKernel_eiKernel_senseDispatchPendingState
#define eiKernel_senseKernel tKernel_eiKernel_senseKernel
#define eiKernel_senseDispatchPendingStateCPU tKernel_eiKernel_senseDispatchPendingStateCPU
#define eiKernel_senseTaskExceptionPendingStateCPU tKernel_eiKernel_senseTaskExceptionPendingStateCPU

/* CB 初期化マクロ #_CIM_# */
#define INITIALIZE_CB()
#define SET_CB_INIB_POINTER(i,p_that)\
	/* empty */
#ifndef TOPPERS_MACRO_ONLY

/* inline ヘッダの include #_INL_# */
#include "tKernel_inline.h"

#endif /* TOPPERS_MACRO_ONLY */

#ifdef TOPPERS_CB_TYPE_ONLY

/* inline のための undef #_UDF_# */
#undef VALID_IDX
#undef GET_CELLCB
#undef CELLCB
#undef CELLIDX
#undef tKernel_IDX
#undef FOREACH_CELL
#undef END_FOREACH_CELL
#undef INITIALIZE_CB
#undef SET_CB_INIB_POINTER
#undef ATTR_accessPattern
#undef tKernel_ATTR_accessPattern
#undef tKernel_GET_accessPattern
#undef eKernel_sleep
#undef eKernel_sleepTimeout
#undef eKernel_delay
#undef eKernel_exitTask
#undef eKernel_getTaskId
#undef eKernel_rotateReadyQueue
#undef eKernel_getTime
#undef eKernel_getMicroTime
#undef eKernel_lockCpu
#undef eKernel_unlockCpu
#undef eKernel_disableDispatch
#undef eKernel_enableDispatch
#undef eKernel_disableTaskException
#undef eKernel_enableTaskException
#undef eKernel_changeInterruptPriorityMask
#undef eKernel_getInterruptPriorityMask
#undef eKernel_exitKernel
#undef eKernel_senseContext
#undef eKernel_senseLock
#undef eKernel_senseDispatch
#undef eKernel_senseDispatchPendingState
#undef eKernel_senseKernel
#undef eiKernel_getTaskId
#undef eiKernel_rotateReadyQueue
#undef eiKernel_getMicroTime
#undef eiKernel_lockCpu
#undef eiKernel_unlockCpu
#undef eiKernel_exitKernel
#undef eiKernel_senseContext
#undef eiKernel_senseLock
#undef eiKernel_senseDispatch
#undef eiKernel_senseDispatchPendingState
#undef eiKernel_senseKernel
#undef eiKernel_senseDispatchPendingStateCPU
#undef eiKernel_senseTaskExceptionPendingStateCPU
#endif /* TOPPERS_CB_TYPE_ONLY */

#endif /* tKernel_TECSGEN_H */
