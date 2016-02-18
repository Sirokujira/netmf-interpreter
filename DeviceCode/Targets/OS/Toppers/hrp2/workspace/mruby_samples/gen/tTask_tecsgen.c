/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#include "tTask_tecsgen.h"
#include "tTask_factory.h"

/* 受け口ディスクリプタ型 #_EDT_# */
/* eTask : omitted by entry port optimize */

/* eiTask : omitted by entry port optimize */

/* 受け口スケルトン関数 #_EPSF_# */
/* eTask : omitted by entry port optimize */
/* eiTask : omitted by entry port optimize */

/* 受け口スケルトン関数テーブル #_EPSFT_# */
/* eTask : omitted by entry port optimize */
/* eiTask : omitted by entry port optimize */

/* ID to INIB table #_INTAB_# */
    extern tTask_INIB  rDomainBridge_EV3Task_INIB;
    extern tTask_INIB  rDomainApplication_MrubyTask1_INIB;
tTask_INIB *tTask_INIB_tab[] ={
    &rDomainBridge_EV3Task_INIB,
    &rDomainApplication_MrubyTask1_INIB,
};
/* CB 初期化コード #_CIC_# */
void
tTask_CB_initialize()
{
    //  tTask_CB	*p_cb;
    int		i;
    FOREACH_CELL(i,p_cb)
        SET_CB_INIB_POINTER(i,p_cb)
        INITIALIZE_CB(p_cb)
    END_FOREACH_CELL
}
