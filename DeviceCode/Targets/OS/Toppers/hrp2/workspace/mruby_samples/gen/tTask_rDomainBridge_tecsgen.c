/*
 * ���Υե������ tecsgen �ˤ�꼫ư��������ޤ���
 * ���Υե�������Խ����ƻ��Ѥ��뤳�Ȥϡ��տޤ���Ƥ��ޤ���
 */
#include "tTask_tecsgen.h"
#include "tTask_factory.h"

/* �������ǥ�������ץ��� #_EDT_# */
/* eTask : omitted by entry port optimize */

/* eiTask : omitted by entry port optimize */

/* �ƤӸ��λ��Ȥ���������ǥ�������ץ�(�ºݤη�����㤷�����) #_CPEPD_# */
extern struct tag_sTaskBody_VDES rDomainBridge_EV3Platform_eTaskBody_des;

/* �ƤӸ����� #_CPA_# */

/* °�����ѿ������� #_AVAI_# */
/* ���� INIB #_INIB_# */
/* cell: rDomainBridge_EV3Task_CB:  EV3Task id=1 */
const tTask_INIB rDomainBridge_EV3Task_INIB = {
    /* call port #_CP_# */ 
    &rDomainBridge_EV3Platform_eTaskBody_des, /* cBody #_CCP1_# */
    /* entry port #_EP_# */ 
    /* attribute(RO) */ 
    TSKID_tTask_EV3Task,                     /* id */
};

/* �������ǥ�������ץ� #_EPD_# */
/* eTask : omitted by entry port optimize */
/* eiTask : omitted by entry port optimize */
