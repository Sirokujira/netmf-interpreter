/*
 * ���Υե������ tecsgen �ˤ�꼫ư��������ޤ���
 * ���Υե�������Խ����ƻ��Ѥ��뤳�Ȥϡ��տޤ���Ƥ��ޤ���
 */
#include "tEV3Platform_tecsgen.h"
#include "tEV3Platform_factory.h"

/* �������ǥ�������ץ��� #_EDT_# */
/* eTaskBody */
struct tag_tEV3Platform_eTaskBody_DES {
    const struct tag_sTaskBody_VMT *vmt;
    int           idx;
};

/* ������������ȥ�ؿ� #_EPSF_# */
/* eTaskBody */
void           tEV3Platform_eTaskBody_main_skel( const struct tag_sTaskBody_VDES *epd)
{
    struct tag_tEV3Platform_eTaskBody_DES *lepd
        = (struct tag_tEV3Platform_eTaskBody_DES *)epd;
    tEV3Platform_eTaskBody_main( lepd->idx );
}

/* ������������ȥ�ؿ��ơ��֥� #_EPSFT_# */
/* eTaskBody */
const struct tag_sTaskBody_VMT tEV3Platform_eTaskBody_MT_ = {
    tEV3Platform_eTaskBody_main_skel,
};

/* �ƤӸ��λ��Ȥ���������ǥ�������ץ�(�ºݤη�����㤷�����) #_CPEPD_# */

/* �ƤӸ����� #_CPA_# */

/* °�����ѿ������� #_AVAI_# */
extern const struct tag_sTaskBody_VMT tEV3Platform_eTaskBody_MT_;
/* �������ǥ�������ץ� #_EPD_# */
extern const struct tag_tEV3Platform_eTaskBody_DES rDomainBridge_EV3Platform_eTaskBody_des;
const struct tag_tEV3Platform_eTaskBody_DES rDomainBridge_EV3Platform_eTaskBody_des = {
    &tEV3Platform_eTaskBody_MT_,
    0,
};
/* CB ����������� #_CIC_# */
void
tEV3Platform_CB_initialize()
{
    //  tEV3Platform_CB	*p_cb;
    int		i;
    FOREACH_CELL(i,p_cb)
        SET_CB_INIB_POINTER(i,p_cb)
        INITIALIZE_CB(p_cb)
    END_FOREACH_CELL
}
