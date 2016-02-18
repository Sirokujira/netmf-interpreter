/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#include "tTask_tecsgen.h"
#include "tTask_factory.h"

/* 受け口ディスクリプタ型 #_EDT_# */
/* eTask : omitted by entry port optimize */

/* eiTask : omitted by entry port optimize */

/* 呼び口の参照する受け口ディスクリプタ(実際の型と相違した定義) #_CPEPD_# */
extern struct tag_sTaskBody_VDES rDomainBridge_EV3Platform_eTaskBody_des;

/* 呼び口配列 #_CPA_# */

/* 属性・変数の配列 #_AVAI_# */
/* セル INIB #_INIB_# */
/* cell: rDomainBridge_EV3Task_CB:  EV3Task id=1 */
const tTask_INIB rDomainBridge_EV3Task_INIB = {
    /* call port #_CP_# */ 
    &rDomainBridge_EV3Platform_eTaskBody_des, /* cBody #_CCP1_# */
    /* entry port #_EP_# */ 
    /* attribute(RO) */ 
    TSKID_tTask_EV3Task,                     /* id */
};

/* 受け口ディスクリプタ #_EPD_# */
/* eTask : omitted by entry port optimize */
/* eiTask : omitted by entry port optimize */
