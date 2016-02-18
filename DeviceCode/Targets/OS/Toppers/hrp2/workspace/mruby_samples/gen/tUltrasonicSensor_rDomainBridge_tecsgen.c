/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#include "tUltrasonicSensor_tecsgen.h"
#include "tUltrasonicSensor_factory.h"

/* 受け口ディスクリプタ型 #_EDT_# */
/* eUltrasonicSensor : omitted by entry port optimize */

/* 受け口スケルトン関数 #_EPSF_# */
/* eUltrasonicSensor : omitted by entry port optimize */

/* 受け口スケルトン関数テーブル #_EPSFT_# */
/* eUltrasonicSensor : omitted by entry port optimize */

/* 呼び口の参照する受け口ディスクリプタ(実際の型と相違した定義) #_CPEPD_# */




/* 呼び口配列 #_CPA_# */




/* 属性・変数の配列 #_AVAI_# */
/* セル INIB #_INIB_# */
tUltrasonicSensor_INIB tUltrasonicSensor_INIB_tab[] = {
    /* cell: tUltrasonicSensor_CB_tab[0]:  UltrasonicSensor1 id=1 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_1,                              /* port */
    },
    /* cell: tUltrasonicSensor_CB_tab[1]:  UltrasonicSensor2 id=2 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_2,                              /* port */
    },
    /* cell: tUltrasonicSensor_CB_tab[2]:  UltrasonicSensor3 id=3 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_3,                              /* port */
    },
    /* cell: tUltrasonicSensor_CB_tab[3]:  UltrasonicSensor4 id=4 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_4,                              /* port */
    },
};

/* 受け口ディスクリプタ #_EPD_# */
/* eUltrasonicSensor : omitted by entry port optimize */
/* eUltrasonicSensor : omitted by entry port optimize */
/* eUltrasonicSensor : omitted by entry port optimize */
/* eUltrasonicSensor : omitted by entry port optimize */
/* CB 初期化コード #_CIC_# */
void
tUltrasonicSensor_CB_initialize()
{
    //  tUltrasonicSensor_CB	*p_cb;
    int		i;
    FOREACH_CELL(i,p_cb)
        SET_CB_INIB_POINTER(i,p_cb)
        INITIALIZE_CB(p_cb)
    END_FOREACH_CELL
}
