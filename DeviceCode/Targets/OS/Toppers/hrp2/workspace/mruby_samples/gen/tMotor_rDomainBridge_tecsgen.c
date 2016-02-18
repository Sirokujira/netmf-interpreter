/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#include "tMotor_tecsgen.h"
#include "tMotor_factory.h"

/* 受け口ディスクリプタ型 #_EDT_# */
/* eMotor : omitted by entry port optimize */

/* 受け口スケルトン関数 #_EPSF_# */
/* eMotor : omitted by entry port optimize */

/* 受け口スケルトン関数テーブル #_EPSFT_# */
/* eMotor : omitted by entry port optimize */

/* 呼び口の参照する受け口ディスクリプタ(実際の型と相違した定義) #_CPEPD_# */




/* 呼び口配列 #_CPA_# */




/* 属性・変数の配列 #_AVAI_# */
/* セル INIB #_INIB_# */
tMotor_INIB tMotor_INIB_tab[] = {
    /* cell: tMotor_CB_tab[0]:  MotorA id=1 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_A,                              /* port */
    },
    /* cell: tMotor_CB_tab[1]:  MotorB id=2 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_B,                              /* port */
    },
    /* cell: tMotor_CB_tab[2]:  MotorC id=3 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_C,                              /* port */
    },
    /* cell: tMotor_CB_tab[3]:  MotorD id=4 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        EV3_PORT_D,                              /* port */
    },
};

/* 受け口ディスクリプタ #_EPD_# */
/* eMotor : omitted by entry port optimize */
/* eMotor : omitted by entry port optimize */
/* eMotor : omitted by entry port optimize */
/* eMotor : omitted by entry port optimize */
/* CB 初期化コード #_CIC_# */
void
tMotor_CB_initialize()
{
    //  tMotor_CB	*p_cb;
    int		i;
    FOREACH_CELL(i,p_cb)
        SET_CB_INIB_POINTER(i,p_cb)
        INITIALIZE_CB(p_cb)
    END_FOREACH_CELL
}
