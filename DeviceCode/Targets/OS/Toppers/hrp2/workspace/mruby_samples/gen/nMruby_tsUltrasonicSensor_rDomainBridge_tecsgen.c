/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#include "nMruby_tsUltrasonicSensor_tecsgen.h"
#include "nMruby_tsUltrasonicSensor_factory.h"


/* 呼び口の参照する受け口ディスクリプタ(実際の型と相違した定義) #_CPEPD_# */
extern struct tag_sUltrasonicSensor_VDES rDomainBridge_UltrasonicSensor1_eUltrasonicSensor_des;

extern struct tag_sUltrasonicSensor_VDES rDomainBridge_UltrasonicSensor2_eUltrasonicSensor_des;

extern struct tag_sUltrasonicSensor_VDES rDomainBridge_UltrasonicSensor3_eUltrasonicSensor_des;

extern struct tag_sUltrasonicSensor_VDES rDomainBridge_UltrasonicSensor4_eUltrasonicSensor_des;

/* 呼び口配列 #_CPA_# */




/* 属性・変数の配列 #_AVAI_# */
/* セル INIB #_INIB_# */
nMruby_tsUltrasonicSensor_INIB nMruby_tsUltrasonicSensor_INIB_tab[] = {
    /* cell: nMruby_tsUltrasonicSensor_CB_tab[0]:  BridgeUltrasonicSensor1 id=1 */
    {
        /* call port #_CP_# */ 
        &tUltrasonicSensor_CB_tab[0],            /* cTECS #_CCP2_# */
    },
    /* cell: nMruby_tsUltrasonicSensor_CB_tab[1]:  BridgeUltrasonicSensor2 id=2 */
    {
        /* call port #_CP_# */ 
        &tUltrasonicSensor_CB_tab[1],            /* cTECS #_CCP2_# */
    },
    /* cell: nMruby_tsUltrasonicSensor_CB_tab[2]:  BridgeUltrasonicSensor3 id=3 */
    {
        /* call port #_CP_# */ 
        &tUltrasonicSensor_CB_tab[2],            /* cTECS #_CCP2_# */
    },
    /* cell: nMruby_tsUltrasonicSensor_CB_tab[3]:  BridgeUltrasonicSensor4 id=4 */
    {
        /* call port #_CP_# */ 
        &tUltrasonicSensor_CB_tab[3],            /* cTECS #_CCP2_# */
    },
};

/* 受け口ディスクリプタ #_EPD_# */
/* CB 初期化コード #_CIC_# */
void
nMruby_tsUltrasonicSensor_CB_initialize()
{
    //  nMruby_tsUltrasonicSensor_CB	*p_cb;
    int		i;
    FOREACH_CELL(i,p_cb)
        SET_CB_INIB_POINTER(i,p_cb)
        INITIALIZE_CB(p_cb)
    END_FOREACH_CELL
}
