/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#include "tGyroSensor_tecsgen.h"
#include "tGyroSensor_factory.h"

/* 受け口ディスクリプタ型 #_EDT_# */
/* eGyroSensor : omitted by entry port optimize */

/* 受け口スケルトン関数 #_EPSF_# */
/* eGyroSensor : omitted by entry port optimize */

/* 受け口スケルトン関数テーブル #_EPSFT_# */
/* eGyroSensor : omitted by entry port optimize */

/* 呼び口の参照する受け口ディスクリプタ(実際の型と相違した定義) #_CPEPD_# */




/* 呼び口配列 #_CPA_# */




/* 属性・変数の配列 #_AVAI_# */
/* セル INIB #_INIB_# */
tGyroSensor_INIB tGyroSensor_INIB_tab[] = {
    /* cell: tGyroSensor_CB_tab[0]:  GyroSensor1 id=1 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_1,                              /* port */
    },
    /* cell: tGyroSensor_CB_tab[1]:  GyroSensor2 id=2 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_2,                              /* port */
    },
    /* cell: tGyroSensor_CB_tab[2]:  GyroSensor3 id=3 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_3,                              /* port */
    },
    /* cell: tGyroSensor_CB_tab[3]:  GyroSensor4 id=4 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_4,                              /* port */
    },
};

/* 受け口ディスクリプタ #_EPD_# */
/* eGyroSensor : omitted by entry port optimize */
/* eGyroSensor : omitted by entry port optimize */
/* eGyroSensor : omitted by entry port optimize */
/* eGyroSensor : omitted by entry port optimize */
/* CB 初期化コード #_CIC_# */
void
tGyroSensor_CB_initialize()
{
    //  tGyroSensor_CB	*p_cb;
    int		i;
    FOREACH_CELL(i,p_cb)
        SET_CB_INIB_POINTER(i,p_cb)
        INITIALIZE_CB(p_cb)
    END_FOREACH_CELL
}
