/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#include "nMruby_tMruby_tecsgen.h"
#include "nMruby_tMruby_factory.h"

/* 受け口ディスクリプタ型 #_EDT_# */
/* eMrubyBody */
struct tag_nMruby_tMruby_eMrubyBody_DES {
    const struct tag_sTaskBody_VMT *vmt;
    tMruby_IDX  idx;
};

/* 受け口スケルトン関数 #_EPSF_# */
/* eMrubyBody */
void           nMruby_tMruby_eMrubyBody_main_skel( const struct tag_sTaskBody_VDES *epd)
{
    struct tag_nMruby_tMruby_eMrubyBody_DES *lepd
        = (struct tag_nMruby_tMruby_eMrubyBody_DES *)epd;
    nMruby_tMruby_eMrubyBody_main( lepd->idx );
}

/* 受け口スケルトン関数テーブル #_EPSFT_# */
/* eMrubyBody */
const struct tag_sTaskBody_VMT nMruby_tMruby_eMrubyBody_MT_ = {
    nMruby_tMruby_eMrubyBody_main_skel,
};

/* 呼び口の参照する受け口ディスクリプタ(実際の型と相違した定義) #_CPEPD_# */

/* 呼び口配列 #_CPA_# */

/* 属性・変数の配列 #_AVAI_# */
/* セル INIB #_INIB_# */
nMruby_tMruby_INIB nMruby_tMruby_INIB_tab[] = {
    /* cell: nMruby_tMruby_CB_tab[0]:  Mruby id=1 */
    {
        /* call port #_CP_# */ 
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        &rDomainApplication_Mruby_irep,          /* irep */
    },
};

extern const struct tag_sTaskBody_VMT nMruby_tMruby_eMrubyBody_MT_;
/* 受け口ディスクリプタ #_EPD_# */
extern const struct tag_nMruby_tMruby_eMrubyBody_DES rDomainApplication_Mruby_eMrubyBody_des;
const struct tag_nMruby_tMruby_eMrubyBody_DES rDomainApplication_Mruby_eMrubyBody_des = {
    &nMruby_tMruby_eMrubyBody_MT_,
    &nMruby_tMruby_INIB_tab[0],   /* INIB */
};
/* CB 初期化コード #_CIC_# */
void
nMruby_tMruby_CB_initialize()
{
    //  nMruby_tMruby_CB	*p_cb;
    int		i;
    FOREACH_CELL(i,p_cb)
        SET_CB_INIB_POINTER(i,p_cb)
        INITIALIZE_CB(p_cb)
    END_FOREACH_CELL
}
