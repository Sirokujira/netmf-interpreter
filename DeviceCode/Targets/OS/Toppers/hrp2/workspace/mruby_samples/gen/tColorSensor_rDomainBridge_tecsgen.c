/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#include "tColorSensor_tecsgen.h"
#include "tColorSensor_factory.h"

/* 受け口ディスクリプタ型 #_EDT_# */
/* eColorSensor : omitted by entry port optimize */

/* 受け口スケルトン関数 #_EPSF_# */
/* eColorSensor : omitted by entry port optimize */

/* 受け口スケルトン関数テーブル #_EPSFT_# */
/* eColorSensor : omitted by entry port optimize */

/* 呼び口の参照する受け口ディスクリプタ(実際の型と相違した定義) #_CPEPD_# */




/* 呼び口配列 #_CPA_# */




/* 属性・変数の配列 #_AVAI_# */
/* セル INIB #_INIB_# */
tColorSensor_INIB tColorSensor_INIB_tab[] = {
    /* cell: tColorSensor_CB_tab[0]:  ColorSensor1 id=1 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_1,                              /* port */
    },
    /* cell: tColorSensor_CB_tab[1]:  ColorSensor2 id=2 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_2,                              /* port */
    },
    /* cell: tColorSensor_CB_tab[2]:  ColorSensor3 id=3 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_3,                              /* port */
    },
    /* cell: tColorSensor_CB_tab[3]:  ColorSensor4 id=4 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_4,                              /* port */
    },
};

/* 受け口ディスクリプタ #_EPD_# */
/* eColorSensor : omitted by entry port optimize */
/* eColorSensor : omitted by entry port optimize */
/* eColorSensor : omitted by entry port optimize */
/* eColorSensor : omitted by entry port optimize */
/* CB 初期化コード #_CIC_# */
void
tColorSensor_CB_initialize()
{
    //  tColorSensor_CB	*p_cb;
    int		i;
    FOREACH_CELL(i,p_cb)
        SET_CB_INIB_POINTER(i,p_cb)
        INITIALIZE_CB(p_cb)
    END_FOREACH_CELL
}
