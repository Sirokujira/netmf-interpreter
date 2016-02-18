/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#include "nMruby_tsTouchSensor_tecsgen.h"
#include "nMruby_tsTouchSensor_factory.h"


/* 呼び口の参照する受け口ディスクリプタ(実際の型と相違した定義) #_CPEPD_# */
extern struct tag_sTouchSensor_VDES rDomainBridge_TouchSensor1_eTouchSensor_des;

extern struct tag_sTouchSensor_VDES rDomainBridge_TouchSensor2_eTouchSensor_des;

extern struct tag_sTouchSensor_VDES rDomainBridge_TouchSensor3_eTouchSensor_des;

extern struct tag_sTouchSensor_VDES rDomainBridge_TouchSensor4_eTouchSensor_des;

/* 呼び口配列 #_CPA_# */




/* 属性・変数の配列 #_AVAI_# */
/* セル INIB #_INIB_# */
nMruby_tsTouchSensor_INIB nMruby_tsTouchSensor_INIB_tab[] = {
    /* cell: nMruby_tsTouchSensor_CB_tab[0]:  BridgeTouchSensor1 id=1 */
    {
        /* call port #_CP_# */ 
        &tTouchSensor_CB_tab[0],                 /* cTECS #_CCP2_# */
    },
    /* cell: nMruby_tsTouchSensor_CB_tab[1]:  BridgeTouchSensor2 id=2 */
    {
        /* call port #_CP_# */ 
        &tTouchSensor_CB_tab[1],                 /* cTECS #_CCP2_# */
    },
    /* cell: nMruby_tsTouchSensor_CB_tab[2]:  BridgeTouchSensor3 id=3 */
    {
        /* call port #_CP_# */ 
        &tTouchSensor_CB_tab[2],                 /* cTECS #_CCP2_# */
    },
    /* cell: nMruby_tsTouchSensor_CB_tab[3]:  BridgeTouchSensor4 id=4 */
    {
        /* call port #_CP_# */ 
        &tTouchSensor_CB_tab[3],                 /* cTECS #_CCP2_# */
    },
};

/* 受け口ディスクリプタ #_EPD_# */
/* CB 初期化コード #_CIC_# */
void
nMruby_tsTouchSensor_CB_initialize()
{
    //  nMruby_tsTouchSensor_CB	*p_cb;
    int		i;
    FOREACH_CELL(i,p_cb)
        SET_CB_INIB_POINTER(i,p_cb)
        INITIALIZE_CB(p_cb)
    END_FOREACH_CELL
}
