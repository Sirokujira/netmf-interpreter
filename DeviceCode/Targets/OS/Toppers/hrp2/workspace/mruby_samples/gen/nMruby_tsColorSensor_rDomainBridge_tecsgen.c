/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#include "nMruby_tsColorSensor_tecsgen.h"
#include "nMruby_tsColorSensor_factory.h"


/* 呼び口の参照する受け口ディスクリプタ(実際の型と相違した定義) #_CPEPD_# */
extern struct tag_sColorSensor_VDES rDomainBridge_ColorSensor1_eColorSensor_des;

extern struct tag_sColorSensor_VDES rDomainBridge_ColorSensor2_eColorSensor_des;

extern struct tag_sColorSensor_VDES rDomainBridge_ColorSensor3_eColorSensor_des;

extern struct tag_sColorSensor_VDES rDomainBridge_ColorSensor4_eColorSensor_des;

/* 呼び口配列 #_CPA_# */




/* 属性・変数の配列 #_AVAI_# */
/* セル INIB #_INIB_# */
nMruby_tsColorSensor_INIB nMruby_tsColorSensor_INIB_tab[] = {
    /* cell: nMruby_tsColorSensor_CB_tab[0]:  BridgeColorSensor1 id=1 */
    {
        /* call port #_CP_# */ 
        &tColorSensor_CB_tab[0],                 /* cTECS #_CCP2_# */
    },
    /* cell: nMruby_tsColorSensor_CB_tab[1]:  BridgeColorSensor2 id=2 */
    {
        /* call port #_CP_# */ 
        &tColorSensor_CB_tab[1],                 /* cTECS #_CCP2_# */
    },
    /* cell: nMruby_tsColorSensor_CB_tab[2]:  BridgeColorSensor3 id=3 */
    {
        /* call port #_CP_# */ 
        &tColorSensor_CB_tab[2],                 /* cTECS #_CCP2_# */
    },
    /* cell: nMruby_tsColorSensor_CB_tab[3]:  BridgeColorSensor4 id=4 */
    {
        /* call port #_CP_# */ 
        &tColorSensor_CB_tab[3],                 /* cTECS #_CCP2_# */
    },
};

/* 受け口ディスクリプタ #_EPD_# */
/* CB 初期化コード #_CIC_# */
void
nMruby_tsColorSensor_CB_initialize()
{
    //  nMruby_tsColorSensor_CB	*p_cb;
    int		i;
    FOREACH_CELL(i,p_cb)
        SET_CB_INIB_POINTER(i,p_cb)
        INITIALIZE_CB(p_cb)
    END_FOREACH_CELL
}
