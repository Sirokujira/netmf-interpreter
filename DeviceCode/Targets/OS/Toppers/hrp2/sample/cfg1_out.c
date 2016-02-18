/* cfg1_out.c */
#define TOPPERS_CFG1_OUT  1
#include "kernel/kernel_int.h"
#include "chip_timer.h"
#include "syssvc/syslog.h"
#include "syssvc/banner.h"
#include "target_serial.h"
#include "syssvc/serial.h"
#include "syssvc/logtask.h"
#include "sample1.h"


#ifdef INT64_MAX
  typedef int64_t signed_t;
  typedef uint64_t unsigned_t;
#else
  typedef int32_t signed_t;
  typedef uint32_t unsigned_t;
#endif

#include "target_cfg1_out.h"

const uint32_t TOPPERS_cfg_magic_number = 0x12345678;
const uint32_t TOPPERS_cfg_sizeof_signed_t = sizeof(signed_t);
const uint32_t TOPPERS_cfg_sizeof_pointer = sizeof(const volatile void*);
const unsigned_t TOPPERS_cfg_CHAR_BIT = ((unsigned char)~0u == 0xff ? 8 : 16);
const unsigned_t TOPPERS_cfg_CHAR_MAX = ((char)-1 < 0 ? (char)((unsigned char)~0u >> 1) : (unsigned char)~0u);
const unsigned_t TOPPERS_cfg_CHAR_MIN = (unsigned_t)((char)-1 < 0 ? -((unsigned char)~0u >> 1) - 1 : 0);
const unsigned_t TOPPERS_cfg_SCHAR_MAX = (signed char)((unsigned char)~0u >> 1);
const unsigned_t TOPPERS_cfg_SHRT_MAX = (short)((unsigned short)~0u >> 1);
const unsigned_t TOPPERS_cfg_INT_MAX = (int)(~0u >> 1);
const unsigned_t TOPPERS_cfg_LONG_MAX = (long)(~0ul >> 1);

const unsigned_t TOPPERS_cfg_TOPPERS_SUPPORT_OVRHDR = 
#if defined(TOPPERS_SUPPORT_OVRHDR)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TOPPERS_SUPPORT_PROTECT = 
#if defined(TOPPERS_SUPPORT_PROTECT)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TOPPERS_SUPPORT_ATT_MOD = 
#if defined(TOPPERS_SUPPORT_ATT_MOD)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TOPPERS_SUPPORT_ATT_PMA = 
#if defined(TOPPERS_SUPPORT_ATT_PMA)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_SIL_ENDIAN_BIG = 
#if defined(SIL_ENDIAN_BIG)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_SIL_ENDIAN_LITTLE = 
#if defined(SIL_ENDIAN_LITTLE)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TA_NULL = ( unsigned_t )TA_NULL;
const unsigned_t TOPPERS_cfg_TA_ACT = ( unsigned_t )TA_ACT;
const unsigned_t TOPPERS_cfg_TA_TPRI = ( unsigned_t )TA_TPRI;
const unsigned_t TOPPERS_cfg_TA_WMUL = ( unsigned_t )TA_WMUL;
const unsigned_t TOPPERS_cfg_TA_CLR = ( unsigned_t )TA_CLR;
const unsigned_t TOPPERS_cfg_TA_CEILING = ( unsigned_t )TA_CEILING;
const unsigned_t TOPPERS_cfg_TA_STA = ( unsigned_t )TA_STA;
const unsigned_t TOPPERS_cfg_TA_NOWRITE = ( unsigned_t )TA_NOWRITE;
const unsigned_t TOPPERS_cfg_TA_NOREAD = ( unsigned_t )TA_NOREAD;
const unsigned_t TOPPERS_cfg_TA_EXEC = ( unsigned_t )TA_EXEC;
const unsigned_t TOPPERS_cfg_TA_MEMINI = ( unsigned_t )TA_MEMINI;
const unsigned_t TOPPERS_cfg_TA_MEMPRSV = ( unsigned_t )TA_MEMPRSV;
const unsigned_t TOPPERS_cfg_TA_SDATA = ( unsigned_t )TA_SDATA;
const unsigned_t TOPPERS_cfg_TA_UNCACHE = ( unsigned_t )TA_UNCACHE;
const unsigned_t TOPPERS_cfg_TA_IODEV = ( unsigned_t )TA_IODEV;
const unsigned_t TOPPERS_cfg_TA_NONKERNEL = ( unsigned_t )TA_NONKERNEL;
const unsigned_t TOPPERS_cfg_TA_ENAINT = ( unsigned_t )TA_ENAINT;
const unsigned_t TOPPERS_cfg_TA_EDGE = ( unsigned_t )TA_EDGE;
const unsigned_t TOPPERS_cfg_TDOM_KERNEL = ( unsigned_t )TDOM_KERNEL;
const unsigned_t TOPPERS_cfg_TDOM_NONE = ( unsigned_t )TDOM_NONE;
const unsigned_t TOPPERS_cfg_TACP_KERNEL = ( unsigned_t )TACP_KERNEL;
const unsigned_t TOPPERS_cfg_TACP_SHARED = ( unsigned_t )TACP_SHARED;
const signed_t TOPPERS_cfg_TMIN_TPRI = ( signed_t )TMIN_TPRI;
const signed_t TOPPERS_cfg_TMAX_TPRI = ( signed_t )TMAX_TPRI;
const signed_t TOPPERS_cfg_TMIN_DPRI = ( signed_t )TMIN_DPRI;
const signed_t TOPPERS_cfg_TMAX_DPRI = ( signed_t )TMAX_DPRI;
const signed_t TOPPERS_cfg_TMIN_ISRPRI = ( signed_t )TMIN_ISRPRI;
const signed_t TOPPERS_cfg_TMAX_ISRPRI = ( signed_t )TMAX_ISRPRI;
const unsigned_t TOPPERS_cfg_TBIT_TEXPTN = ( unsigned_t )TBIT_TEXPTN;
const unsigned_t TOPPERS_cfg_TBIT_FLGPTN = ( unsigned_t )TBIT_FLGPTN;
const unsigned_t TOPPERS_cfg_TMAX_MAXSEM = ( unsigned_t )TMAX_MAXSEM;
const unsigned_t TOPPERS_cfg_TMAX_RELTIM = ( unsigned_t )TMAX_RELTIM;
const signed_t TOPPERS_cfg_TMIN_INTPRI = ( signed_t )TMIN_INTPRI;
const unsigned_t TOPPERS_cfg_TOPPERS_ATTSEC = ( unsigned_t )TOPPERS_ATTSEC;
const unsigned_t TOPPERS_cfg_TOPPERS_ATTMEM = ( unsigned_t )TOPPERS_ATTMEM;
const unsigned_t TOPPERS_cfg_TOPPERS_USTACK = ( unsigned_t )TOPPERS_USTACK;
const unsigned_t TOPPERS_cfg_OMIT_STANDARD_MEMINIB = 
#if defined(OMIT_STANDARD_MEMINIB)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_OMIT_INITIALIZE_INTERRUPT = 
#if defined(OMIT_INITIALIZE_INTERRUPT)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_OMIT_INITIALIZE_EXCEPTION = 
#if defined(OMIT_INITIALIZE_EXCEPTION)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_OMIT_IDATA = 
#if defined(OMIT_IDATA)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_OMIT_CHECK_USTACK_OVERLAP = 
#if defined(OMIT_CHECK_USTACK_OVERLAP)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_OMIT_STANDARD_DATASECINIB = 
#if defined(OMIT_STANDARD_DATASECINIB)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_OMIT_STANDARD_BSSSECINIB = 
#if defined(OMIT_STANDARD_BSSSECINIB)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_USE_CFG_PASS3 = 
#if defined(USE_CFG_PASS3)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_USE_LATERPASS_DOMINIB = 
#if defined(USE_LATERPASS_DOMINIB)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_USE_DOMINICTXB = 
#if defined(USE_DOMINICTXB)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_USE_TSKINICTXB = 
#if defined(USE_TSKINICTXB)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_USE_REDZONE = 
#if defined(USE_REDZONE)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_TSKATR = 
#if defined(TARGET_TSKATR)
(TARGET_TSKATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_REGATR = 
#if defined(TARGET_REGATR)
(TARGET_REGATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_MEMATR = 
#if defined(TARGET_MEMATR)
(TARGET_MEMATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_INTATR = 
#if defined(TARGET_INTATR)
(TARGET_INTATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_INHATR = 
#if defined(TARGET_INHATR)
(TARGET_INHATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_ISRATR = 
#if defined(TARGET_ISRATR)
(TARGET_ISRATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_EXCATR = 
#if defined(TARGET_EXCATR)
(TARGET_EXCATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_SVCATR = 
#if defined(TARGET_SVCATR)
(TARGET_SVCATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_MIN_SSTKSZ = 
#if defined(TARGET_MIN_SSTKSZ)
(TARGET_MIN_SSTKSZ);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_MIN_USTKSZ = 
#if defined(TARGET_MIN_USTKSZ)
(TARGET_MIN_USTKSZ);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_MIN_ISTKSZ = 
#if defined(TARGET_MIN_ISTKSZ)
(TARGET_MIN_ISTKSZ);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_DUMMY_STKSZ = 
#if defined(TARGET_DUMMY_STKSZ)
(TARGET_DUMMY_STKSZ);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_STKSZ_ALIGN = 
#if defined(CHECK_STKSZ_ALIGN)
(CHECK_STKSZ_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_USTKSZ_ALIGN = 
#if defined(CHECK_USTKSZ_ALIGN)
(CHECK_USTKSZ_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_FUNC_ALIGN = 
#if defined(CHECK_FUNC_ALIGN)
(CHECK_FUNC_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_FUNC_NONNULL = 
#if defined(CHECK_FUNC_NONNULL)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_STACK_ALIGN = 
#if defined(CHECK_STACK_ALIGN)
(CHECK_STACK_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_STACK_NONNULL = 
#if defined(CHECK_STACK_NONNULL)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_USTACK_ALIGN = 
#if defined(CHECK_USTACK_ALIGN)
(CHECK_USTACK_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_USTACK_NONNULL = 
#if defined(CHECK_USTACK_NONNULL)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_MPF_ALIGN = 
#if defined(CHECK_MPF_ALIGN)
(CHECK_MPF_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_MPF_NONNULL = 
#if defined(CHECK_MPF_NONNULL)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_MB_ALIGN = 
#if defined(CHECK_MB_ALIGN)
(CHECK_MB_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TOPPERS_LABEL_ASM = 
#if defined(TOPPERS_LABEL_ASM)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_ID = ( unsigned_t )sizeof(ID);
const unsigned_t TOPPERS_cfg_sizeof_uint_t = ( unsigned_t )sizeof(uint_t);
const unsigned_t TOPPERS_cfg_sizeof_SIZE = ( unsigned_t )sizeof(SIZE);
const unsigned_t TOPPERS_cfg_sizeof_ATR = ( unsigned_t )sizeof(ATR);
const unsigned_t TOPPERS_cfg_sizeof_PRI = ( unsigned_t )sizeof(PRI);
const unsigned_t TOPPERS_cfg_sizeof_void_ptr = ( unsigned_t )sizeof(void*);
const unsigned_t TOPPERS_cfg_sizeof_VP = ( unsigned_t )sizeof(void*);
const unsigned_t TOPPERS_cfg_sizeof_intptr_t = ( unsigned_t )sizeof(intptr_t);
const unsigned_t TOPPERS_cfg_sizeof_FP = ( unsigned_t )sizeof(FP);
const unsigned_t TOPPERS_cfg_sizeof_ACPTN = ( unsigned_t )sizeof(ACPTN);
const unsigned_t TOPPERS_cfg_sizeof_ACVCT = ( unsigned_t )sizeof(ACVCT);
const unsigned_t TOPPERS_cfg_offsetof_ACVCT_acptn1 = ( unsigned_t )offsetof(ACVCT,acptn1);
const unsigned_t TOPPERS_cfg_offsetof_ACVCT_acptn2 = ( unsigned_t )offsetof(ACVCT,acptn2);
const unsigned_t TOPPERS_cfg_offsetof_ACVCT_acptn3 = ( unsigned_t )offsetof(ACVCT,acptn3);
const unsigned_t TOPPERS_cfg_offsetof_ACVCT_acptn4 = ( unsigned_t )offsetof(ACVCT,acptn4);
const unsigned_t TOPPERS_cfg_sizeof_INHNO = ( unsigned_t )sizeof(INHNO);
const unsigned_t TOPPERS_cfg_sizeof_INTNO = ( unsigned_t )sizeof(INTNO);
const unsigned_t TOPPERS_cfg_sizeof_EXCNO = ( unsigned_t )sizeof(EXCNO);
const unsigned_t TOPPERS_cfg_sizeof_DOMINIB = ( unsigned_t )sizeof(DOMINIB);
const unsigned_t TOPPERS_cfg_offsetof_DOMINIB_domptn = ( unsigned_t )offsetof(DOMINIB,domptn);
const unsigned_t TOPPERS_cfg_sizeof_MEMINIB = ( unsigned_t )sizeof(MEMINIB);
const unsigned_t TOPPERS_cfg_offsetof_MEMINIB_mematr = 
#if !defined(OMIT_STANDARD_MEMINIB)
(offsetof(MEMINIB,mematr));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_MEMINIB_acptn4 = 
#if !defined(OMIT_STANDARD_MEMINIB)
(offsetof(MEMINIB,acptn4));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_MEMINIB_acptn1 = 
#if !defined(OMIT_STANDARD_MEMINIB)
(offsetof(MEMINIB,acptn1));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_MEMINIB_acptn2 = 
#if !defined(OMIT_STANDARD_MEMINIB)
(offsetof(MEMINIB,acptn2));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_TINIB = ( unsigned_t )sizeof(TINIB);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_p_dominib = ( unsigned_t )offsetof(TINIB,p_dominib);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_tskatr = ( unsigned_t )offsetof(TINIB,tskatr);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_exinf = ( unsigned_t )offsetof(TINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_task = ( unsigned_t )offsetof(TINIB,task);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_ipriority = ( unsigned_t )offsetof(TINIB,ipriority);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_sstksz = 
#if !defined(USE_TSKINICTXB)
(offsetof(TINIB,sstksz));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_TINIB_sstk = 
#if !defined(USE_TSKINICTXB)
(offsetof(TINIB,sstk));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_TINIB_ustksz = 
#if !defined(USE_TSKINICTXB)
(offsetof(TINIB,ustksz));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_TINIB_ustk = 
#if !defined(USE_TSKINICTXB)
(offsetof(TINIB,ustk));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_TINIB_texatr = ( unsigned_t )offsetof(TINIB,texatr);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_texrtn = ( unsigned_t )offsetof(TINIB,texrtn);
const unsigned_t TOPPERS_cfg_sizeof_SEMINIB = ( unsigned_t )sizeof(SEMINIB);
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_sematr = ( unsigned_t )offsetof(SEMINIB,sematr);
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_isemcnt = ( unsigned_t )offsetof(SEMINIB,isemcnt);
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_maxsem = ( unsigned_t )offsetof(SEMINIB,maxsem);
const unsigned_t TOPPERS_cfg_sizeof_FLGPTN = ( unsigned_t )sizeof(FLGPTN);
const unsigned_t TOPPERS_cfg_sizeof_FLGINIB = ( unsigned_t )sizeof(FLGINIB);
const unsigned_t TOPPERS_cfg_offsetof_FLGINIB_flgatr = ( unsigned_t )offsetof(FLGINIB,flgatr);
const unsigned_t TOPPERS_cfg_offsetof_FLGINIB_iflgptn = ( unsigned_t )offsetof(FLGINIB,iflgptn);
const unsigned_t TOPPERS_cfg_sizeof_DTQINIB = ( unsigned_t )sizeof(DTQINIB);
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_dtqatr = ( unsigned_t )offsetof(DTQINIB,dtqatr);
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_dtqcnt = ( unsigned_t )offsetof(DTQINIB,dtqcnt);
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_p_dtqmb = ( unsigned_t )offsetof(DTQINIB,p_dtqmb);
const unsigned_t TOPPERS_cfg_sizeof_PDQINIB = ( unsigned_t )sizeof(PDQINIB);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_pdqatr = ( unsigned_t )offsetof(PDQINIB,pdqatr);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_pdqcnt = ( unsigned_t )offsetof(PDQINIB,pdqcnt);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_maxdpri = ( unsigned_t )offsetof(PDQINIB,maxdpri);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_p_pdqmb = ( unsigned_t )offsetof(PDQINIB,p_pdqmb);
const unsigned_t TOPPERS_cfg_sizeof_MTXINIB = ( unsigned_t )sizeof(MTXINIB);
const unsigned_t TOPPERS_cfg_offsetof_MTXINIB_mtxatr = ( unsigned_t )offsetof(MTXINIB,mtxatr);
const unsigned_t TOPPERS_cfg_offsetof_MTXINIB_ceilpri = ( unsigned_t )offsetof(MTXINIB,ceilpri);
const unsigned_t TOPPERS_cfg_sizeof_MPFINIB = ( unsigned_t )sizeof(MPFINIB);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_mpfatr = ( unsigned_t )offsetof(MPFINIB,mpfatr);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_blkcnt = ( unsigned_t )offsetof(MPFINIB,blkcnt);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_blksz = ( unsigned_t )offsetof(MPFINIB,blksz);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_mpf = ( unsigned_t )offsetof(MPFINIB,mpf);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_p_mpfmb = ( unsigned_t )offsetof(MPFINIB,p_mpfmb);
const unsigned_t TOPPERS_cfg_sizeof_CYCINIB = ( unsigned_t )sizeof(CYCINIB);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cycatr = ( unsigned_t )offsetof(CYCINIB,cycatr);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_exinf = ( unsigned_t )offsetof(CYCINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cychdr = ( unsigned_t )offsetof(CYCINIB,cychdr);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cyctim = ( unsigned_t )offsetof(CYCINIB,cyctim);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cycphs = ( unsigned_t )offsetof(CYCINIB,cycphs);
const unsigned_t TOPPERS_cfg_sizeof_ALMINIB = ( unsigned_t )sizeof(ALMINIB);
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_almatr = ( unsigned_t )offsetof(ALMINIB,almatr);
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_exinf = ( unsigned_t )offsetof(ALMINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_almhdr = ( unsigned_t )offsetof(ALMINIB,almhdr);
const unsigned_t TOPPERS_cfg_sizeof_OVRINIB = 
#if defined(TOPPERS_SUPPORT_OVRHDR)
(sizeof(OVRINIB));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_OVRINIB_ovratr = 
#if defined(TOPPERS_SUPPORT_OVRHDR)
(offsetof(OVRINIB,ovratr));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_OVRINIB_ovrhdr = 
#if defined(TOPPERS_SUPPORT_OVRHDR)
(offsetof(OVRINIB,ovrhdr));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_ISRINIB = ( unsigned_t )sizeof(ISRINIB);
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_isratr = ( unsigned_t )offsetof(ISRINIB,isratr);
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_exinf = ( unsigned_t )offsetof(ISRINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_intno = ( unsigned_t )offsetof(ISRINIB,intno);
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_p_isr_queue = ( unsigned_t )offsetof(ISRINIB,p_isr_queue);
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_isr = ( unsigned_t )offsetof(ISRINIB,isr);
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_isrpri = ( unsigned_t )offsetof(ISRINIB,isrpri);
const unsigned_t TOPPERS_cfg_sizeof_INHINIB = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(sizeof(INHINIB));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INHINIB_inhno = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INHINIB,inhno));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INHINIB_inhatr = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INHINIB,inhatr));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INHINIB_int_entry = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INHINIB,int_entry));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_INTINIB = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(sizeof(INTINIB));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INTINIB_intno = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INTINIB,intno));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INTINIB_intatr = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INTINIB,intatr));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INTINIB_intpri = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INTINIB,intpri));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_EXCINIB = 
#if !defined(OMIT_INITIALIZE_EXCEPTION)
(sizeof(EXCINIB));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_EXCINIB_excno = 
#if !defined(OMIT_INITIALIZE_EXCEPTION)
(offsetof(EXCINIB,excno));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_EXCINIB_excatr = 
#if !defined(OMIT_INITIALIZE_EXCEPTION)
(offsetof(EXCINIB,excatr));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_EXCINIB_exc_entry = 
#if !defined(OMIT_INITIALIZE_EXCEPTION)
(offsetof(EXCINIB,exc_entry));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_SVCINIB = ( unsigned_t )sizeof(SVCINIB);
const unsigned_t TOPPERS_cfg_offsetof_SVCINIB_svcrtn = ( unsigned_t )offsetof(SVCINIB,svcrtn);
const unsigned_t TOPPERS_cfg_offsetof_SVCINIB_stksz = ( unsigned_t )offsetof(SVCINIB,stksz);
const unsigned_t TOPPERS_cfg_TMAX_INTNO = ( unsigned_t )TMAX_INTNO;
const unsigned_t TOPPERS_cfg_TMIN_INTNO = ( unsigned_t )TMIN_INTNO;
const unsigned_t TOPPERS_cfg_TMAX_INTPRI = ( unsigned_t )TMAX_INTPRI;
const unsigned_t TOPPERS_cfg_TA_SORDER = ( unsigned_t )TA_SORDER;
const unsigned_t TOPPERS_cfg_TA_WTHROUGH = ( unsigned_t )TA_WTHROUGH;
const unsigned_t TOPPERS_cfg_TA_NONSHARED = ( unsigned_t )TA_NONSHARED;
const unsigned_t TOPPERS_cfg_ARM_SSECTION_SIZE = ( unsigned_t )ARM_SSECTION_SIZE;
const unsigned_t TOPPERS_cfg_ARM_SECTION_SIZE = ( unsigned_t )ARM_SECTION_SIZE;
const unsigned_t TOPPERS_cfg_ARM_LPAGE_SIZE = ( unsigned_t )ARM_LPAGE_SIZE;
const unsigned_t TOPPERS_cfg_ARM_PAGE_SIZE = ( unsigned_t )ARM_PAGE_SIZE;
const unsigned_t TOPPERS_cfg_ARM_SECTION_TABLE_SIZE = ( unsigned_t )ARM_SECTION_TABLE_SIZE;
const unsigned_t TOPPERS_cfg_ARM_SECTION_TABLE_ALIGN = ( unsigned_t )ARM_SECTION_TABLE_ALIGN;
const unsigned_t TOPPERS_cfg_ARM_SECTION_TABLE_ENTRY = ( unsigned_t )ARM_SECTION_TABLE_ENTRY;
const unsigned_t TOPPERS_cfg_ARM_PAGE_TABLE_SIZE = ( unsigned_t )ARM_PAGE_TABLE_SIZE;
const unsigned_t TOPPERS_cfg_ARM_PAGE_TABLE_ALIGN = ( unsigned_t )ARM_PAGE_TABLE_ALIGN;
const unsigned_t TOPPERS_cfg_ARM_PAGE_TABLE_ENTRY = ( unsigned_t )ARM_PAGE_TABLE_ENTRY;
const unsigned_t TOPPERS_cfg_TOPPERS_MPCORE = 
#if defined(TOPPERS_MPCORE)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_TCB = ( unsigned_t )sizeof(TCB);
const unsigned_t TOPPERS_cfg_offsetof_TCB_p_tinib = ( unsigned_t )offsetof(TCB,p_tinib);
const unsigned_t TOPPERS_cfg_offsetof_TCB_svclevel = ( unsigned_t )offsetof(TCB,svclevel);
const unsigned_t TOPPERS_cfg_offsetof_TCB_texptn = ( unsigned_t )offsetof(TCB,texptn);
const unsigned_t TOPPERS_cfg_offsetof_TCB_sp = ( unsigned_t )offsetof(TCB,tskctxb.sp);
const unsigned_t TOPPERS_cfg_offsetof_TCB_pc = ( unsigned_t )offsetof(TCB,tskctxb.pc);
const unsigned_t TOPPERS_cfg_offsetof_TCB_priv = ( unsigned_t )offsetof(TCB,tskctxb.priv);
const unsigned_t TOPPERS_cfg_offsetof_DOMINIB_domid = ( unsigned_t )offsetof(DOMINIB,domctxb.domid);
const unsigned_t TOPPERS_cfg_offsetof_DOMINIB_p_section_table = ( unsigned_t )offsetof(DOMINIB,domctxb.p_section_table);
// const unsigned_t TOPPERS_cfg_ev3cyc = ( unsigned_t )EV3_CRE_CYC;

#define DOM1	1
#define DOM2	2


#line 6 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_0 = 0;
const char TOPPERS_cfg_valueof_region_0[] = "ROM"; const unsigned_t TOPPERS_cfg_valueof_regatr_0 = ( unsigned_t )( TA_NOWRITE ); const unsigned_t TOPPERS_cfg_valueof_base_0 = ( unsigned_t )( 0xC0008000 ); const unsigned_t TOPPERS_cfg_valueof_size_0 = ( unsigned_t )( 0x00100000 ); 
#line 7 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_1 = 1;
const char TOPPERS_cfg_valueof_region_1[] = "RAM"; const unsigned_t TOPPERS_cfg_valueof_regatr_1 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_base_1 = ( unsigned_t )( 0xC0108000 ); const unsigned_t TOPPERS_cfg_valueof_size_1 = ( unsigned_t )( 0x03EF8000 ); 
#line 8 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_2 = 2;
const char TOPPERS_cfg_valueof_stdrom_2[] = "ROM"; const char TOPPERS_cfg_valueof_stdram_2[] = "RAM"; 
#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 10 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL

#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 15 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 20 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_3 = ( unsigned_t ) ( TDOM_KERNEL );
#line 21 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_3 = 3;
const unsigned_t TOPPERS_cfg_valueof_mematr_3 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_3 = ( unsigned_t )( 0x00009000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_4 = ( unsigned_t ) ( TDOM_KERNEL );
#line 22 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_4 = 4;
const unsigned_t TOPPERS_cfg_valueof_mematr_4 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_4 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_5 = ( unsigned_t ) ( TDOM_KERNEL );
#line 23 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_5 = 5;
const unsigned_t TOPPERS_cfg_valueof_mematr_5 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_5 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_6 = ( unsigned_t ) ( TDOM_KERNEL );
#line 24 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_6 = 6;
const unsigned_t TOPPERS_cfg_valueof_mematr_6 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_6 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_7 = ( unsigned_t ) ( TDOM_KERNEL );
#line 25 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_7 = 7;
const unsigned_t TOPPERS_cfg_valueof_mematr_7 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_7 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_8 = ( unsigned_t ) ( TDOM_KERNEL );
#line 26 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_8 = 8;
const unsigned_t TOPPERS_cfg_valueof_mematr_8 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_8 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_9 = ( unsigned_t ) ( TDOM_KERNEL );
#line 27 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_9 = 9;
const unsigned_t TOPPERS_cfg_valueof_mematr_9 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_9 = ( unsigned_t )( 0x00010000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_10 = ( unsigned_t ) ( TDOM_KERNEL );
#line 28 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_10 = 10;
const unsigned_t TOPPERS_cfg_valueof_mematr_10 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_10 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_11 = ( unsigned_t ) ( TDOM_KERNEL );
#line 29 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_11 = 11;
const unsigned_t TOPPERS_cfg_valueof_mematr_11 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_11 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_12 = ( unsigned_t ) ( TDOM_KERNEL );
#line 30 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_12 = 12;
const unsigned_t TOPPERS_cfg_valueof_mematr_12 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_12 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_13 = ( unsigned_t ) ( TDOM_KERNEL );
#line 31 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_13 = 13;
const unsigned_t TOPPERS_cfg_valueof_mematr_13 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_13 = ( unsigned_t )( 0x00003000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_14 = ( unsigned_t ) ( TDOM_KERNEL );
#line 32 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_14 = 14;
const unsigned_t TOPPERS_cfg_valueof_mematr_14 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_14 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_15 = ( unsigned_t ) ( TDOM_KERNEL );
#line 33 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_15 = 15;
const unsigned_t TOPPERS_cfg_valueof_mematr_15 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_15 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_16 = ( unsigned_t ) ( TDOM_KERNEL );
#line 34 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_16 = 16;
const unsigned_t TOPPERS_cfg_valueof_mematr_16 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_16 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_17 = ( unsigned_t ) ( TDOM_KERNEL );
#line 35 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_17 = 17;
const unsigned_t TOPPERS_cfg_valueof_mematr_17 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_17 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_18 = ( unsigned_t ) ( TDOM_KERNEL );
#line 36 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_18 = 18;
const unsigned_t TOPPERS_cfg_valueof_mematr_18 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_18 = ( unsigned_t )( 0x00009000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_19 = ( unsigned_t ) ( TDOM_KERNEL );
#line 37 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_19 = 19;
const unsigned_t TOPPERS_cfg_valueof_mematr_19 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_19 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_20 = ( unsigned_t ) ( TDOM_KERNEL );
#line 38 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_20 = 20;
const unsigned_t TOPPERS_cfg_valueof_mematr_20 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_20 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_21 = ( unsigned_t ) ( TDOM_KERNEL );
#line 39 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_21 = 21;
const unsigned_t TOPPERS_cfg_valueof_mematr_21 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_21 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_22 = ( unsigned_t ) ( TDOM_KERNEL );
#line 40 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_22 = 22;
const unsigned_t TOPPERS_cfg_valueof_mematr_22 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_22 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_23 = ( unsigned_t ) ( TDOM_KERNEL );
#line 41 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_23 = 23;
const unsigned_t TOPPERS_cfg_valueof_mematr_23 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_23 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_24 = ( unsigned_t ) ( TDOM_KERNEL );
#line 42 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_24 = 24;
const unsigned_t TOPPERS_cfg_valueof_mematr_24 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_24 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_25 = ( unsigned_t ) ( TDOM_KERNEL );
#line 43 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_25 = 25;
const unsigned_t TOPPERS_cfg_valueof_mematr_25 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_25 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_26 = ( unsigned_t ) ( TDOM_KERNEL );
#line 44 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_26 = 26;
const unsigned_t TOPPERS_cfg_valueof_mematr_26 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_26 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_27 = ( unsigned_t ) ( TDOM_KERNEL );
#line 45 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_27 = 27;
const unsigned_t TOPPERS_cfg_valueof_mematr_27 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_27 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_28 = ( unsigned_t ) ( TDOM_KERNEL );
#line 46 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_28 = 28;
const unsigned_t TOPPERS_cfg_valueof_mematr_28 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_28 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_29 = ( unsigned_t ) ( TDOM_KERNEL );
#line 47 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_29 = 29;
const unsigned_t TOPPERS_cfg_valueof_mematr_29 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_29 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_30 = ( unsigned_t ) ( TDOM_KERNEL );
#line 49 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_30 = 30;
const unsigned_t TOPPERS_cfg_valueof_mematr_30 = ( unsigned_t )( TA_NOWRITE|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_30 = ( unsigned_t )( 0x0000C000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_31 = ( unsigned_t ) ( TDOM_KERNEL );
#line 51 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_31 = 31;
const unsigned_t TOPPERS_cfg_valueof_mematr_31 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_31 = ( unsigned_t )( 0x00020000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_32 = ( unsigned_t ) ( TDOM_KERNEL );
#line 53 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_32 = 32;
const unsigned_t TOPPERS_cfg_valueof_mematr_32 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_32 = ( unsigned_t )( 0x00002000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_33 = ( unsigned_t ) ( TDOM_KERNEL );
#line 55 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_33 = 33;
const unsigned_t TOPPERS_cfg_valueof_mematr_33 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_33 = ( unsigned_t )( 0x00002000 ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 57 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_mem.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#if 0 

#endif
/* #include "chip_timer.h" */

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 8 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/arch/arm_gcc/am1808/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_34 = ( unsigned_t ) ( TDOM_KERNEL );
#line 11 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/arch/arm_gcc/am1808/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_34 = 34;
const unsigned_t TOPPERS_cfg_valueof_iniatr_34 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_35 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/arch/arm_gcc/am1808/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_35 = 35;
const unsigned_t TOPPERS_cfg_valueof_teratr_35 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_36 = ( unsigned_t ) ( TDOM_KERNEL );
#line 13 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/arch/arm_gcc/am1808/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_36 = 36;
const unsigned_t TOPPERS_cfg_valueof_intno_36 = ( unsigned_t )( INTNO_TIMER ); const unsigned_t TOPPERS_cfg_valueof_intatr_36 = ( unsigned_t )( TA_ENAINT|INTATR_TIMER ); const signed_t TOPPERS_cfg_valueof_intpri_36 = ( signed_t )( INTPRI_TIMER ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_37 = ( unsigned_t ) ( TDOM_KERNEL );
#line 14 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/arch/arm_gcc/am1808/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_37 = 37;
const unsigned_t TOPPERS_cfg_valueof_isratr_37 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_37 = ( unsigned_t )( INTNO_TIMER ); const signed_t TOPPERS_cfg_valueof_isrpri_37 = ( signed_t )( TMIN_ISRPRI ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 25 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/arch/arm_gcc/am1808/chip_timer.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL

/* #include "syssvc/syslog.h" */

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 11 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_38 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_38 = 38;
const unsigned_t TOPPERS_cfg_valueof_iniatr_38 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_39 = ( unsigned_t ) ( TDOM_KERNEL );
#line 13 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_39 = 39;
const char TOPPERS_cfg_valueof_module_39[] = "syslog.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_40 = ( unsigned_t ) ( TDOM_KERNEL );
#line 15 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_40 = 40;
const unsigned_t TOPPERS_cfg_valueof_fncd_40 = ( unsigned_t )( TFN_SYSLOG_WRI_LOG ); const unsigned_t TOPPERS_cfg_valueof_svcatr_40 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_40 = ( unsigned_t )( SSZ_SYSLOG_WRI_LOG ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_41 = ( unsigned_t ) ( TDOM_KERNEL );
#line 17 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_41 = 41;
const unsigned_t TOPPERS_cfg_valueof_fncd_41 = ( unsigned_t )( TFN_SYSLOG_FWRI_LOG ); const unsigned_t TOPPERS_cfg_valueof_svcatr_41 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_41 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_42 = ( unsigned_t ) ( TDOM_KERNEL );
#line 18 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_42 = 42;
const unsigned_t TOPPERS_cfg_valueof_fncd_42 = ( unsigned_t )( TFN_SYSLOG_REA_LOG ); const unsigned_t TOPPERS_cfg_valueof_svcatr_42 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_42 = ( unsigned_t )( SSZ_SYSLOG_REA_LOG ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_43 = ( unsigned_t ) ( TDOM_KERNEL );
#line 20 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_43 = 43;
const unsigned_t TOPPERS_cfg_valueof_fncd_43 = ( unsigned_t )( TFN_SYSLOG_MSK_LOG ); const unsigned_t TOPPERS_cfg_valueof_svcatr_43 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_43 = ( unsigned_t )( SSZ_SYSLOG_MSK_LOG ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_44 = ( unsigned_t ) ( TDOM_KERNEL );
#line 22 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_44 = 44;
const unsigned_t TOPPERS_cfg_valueof_fncd_44 = ( unsigned_t )( TFN_SYSLOG_REF_LOG ); const unsigned_t TOPPERS_cfg_valueof_svcatr_44 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_44 = ( unsigned_t )( SSZ_SYSLOG_REF_LOG ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 24 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/syslog.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL

/* #include "syssvc/banner.h" */

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 11 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_45 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_static_api_45 = 45;
const unsigned_t TOPPERS_cfg_valueof_iniatr_45 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_46 = ( unsigned_t ) ( TDOM_KERNEL );
#line 13 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_static_api_46 = 46;
const char TOPPERS_cfg_valueof_module_46[] = "banner.o"; 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 14 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/banner.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL

/* #include "target_serial.h" */

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 7 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_47 = ( unsigned_t ) ( TDOM_KERNEL );
#line 9 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_47 = 47;
const unsigned_t TOPPERS_cfg_valueof_iniatr_47 = ( unsigned_t )( TA_NULL ); 
#if defined(BUILD_EV3_PLATFORM)
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_48 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_48 = 48;
#define BT_SIO_CYC	(<>)

#line 12 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_48 = ( unsigned_t )( TA_STA ); const unsigned_t TOPPERS_cfg_valueof_cyctim_48 = ( unsigned_t )( 5 ); const unsigned_t TOPPERS_cfg_valueof_cycphs_48 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_49 = ( unsigned_t ) ( TDOM_KERNEL );
#line 13 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_49 = 49;
#define BT_RCV_ALM	(<>)

#line 13 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_almatr_49 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_50 = ( unsigned_t ) ( TDOM_KERNEL );
#line 14 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_50 = 50;
#define BT_SND_BUF_SEM	(<>)

#line 14 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_50 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_50 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_50 = ( unsigned_t )( 1 ); 
#endif

#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 17 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#if 0 

#if !ENABLE_UART1_SENSOR

#line 21 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_51 = 51;
const unsigned_t TOPPERS_cfg_valueof_isratr_51 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_51 = ( unsigned_t )( UART1_INT ); const signed_t TOPPERS_cfg_valueof_isrpri_51 = ( signed_t )( TMIN_ISRPRI ); 
#line 22 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/target/ev3_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_52 = 52;
const unsigned_t TOPPERS_cfg_valueof_intno_52 = ( unsigned_t )( UART1_INT ); const unsigned_t TOPPERS_cfg_valueof_intatr_52 = ( unsigned_t )( 0 ); const signed_t TOPPERS_cfg_valueof_intpri_52 = ( signed_t )( INTPRI_UART_SIO ); 
#endif

#endif
/* #include "syssvc/serial.h" */

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 13 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_53 = ( unsigned_t ) ( TDOM_KERNEL );
#line 14 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_53 = 53;
const unsigned_t TOPPERS_cfg_valueof_iniatr_53 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_54 = ( unsigned_t ) ( TDOM_KERNEL );
#line 15 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_54 = 54;
const char TOPPERS_cfg_valueof_module_54[] = "serial.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_55 = ( unsigned_t ) ( TDOM_KERNEL );
#line 17 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_55 = 55;
const unsigned_t TOPPERS_cfg_valueof_fncd_55 = ( unsigned_t )( TFN_SERIAL_OPN_POR ); const unsigned_t TOPPERS_cfg_valueof_svcatr_55 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_55 = ( unsigned_t )( SSZ_SERIAL_OPN_POR ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_56 = ( unsigned_t ) ( TDOM_KERNEL );
#line 19 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_56 = 56;
const unsigned_t TOPPERS_cfg_valueof_fncd_56 = ( unsigned_t )( TFN_SERIAL_CLS_POR ); const unsigned_t TOPPERS_cfg_valueof_svcatr_56 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_56 = ( unsigned_t )( SSZ_SERIAL_CLS_POR ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_57 = ( unsigned_t ) ( TDOM_KERNEL );
#line 21 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_57 = 57;
const unsigned_t TOPPERS_cfg_valueof_fncd_57 = ( unsigned_t )( TFN_SERIAL_REA_DAT ); const unsigned_t TOPPERS_cfg_valueof_svcatr_57 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_57 = ( unsigned_t )( SSZ_SERIAL_REA_DAT ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_58 = ( unsigned_t ) ( TDOM_KERNEL );
#line 23 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_58 = 58;
const unsigned_t TOPPERS_cfg_valueof_fncd_58 = ( unsigned_t )( TFN_SERIAL_WRI_DAT ); const unsigned_t TOPPERS_cfg_valueof_svcatr_58 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_58 = ( unsigned_t )( SSZ_SERIAL_WRI_DAT ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_59 = ( unsigned_t ) ( TDOM_KERNEL );
#line 25 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_59 = 59;
const unsigned_t TOPPERS_cfg_valueof_fncd_59 = ( unsigned_t )( TFN_SERIAL_CTL_POR ); const unsigned_t TOPPERS_cfg_valueof_svcatr_59 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_59 = ( unsigned_t )( SSZ_SERIAL_CTL_POR ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_60 = ( unsigned_t ) ( TDOM_KERNEL );
#line 27 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_60 = 60;
const unsigned_t TOPPERS_cfg_valueof_fncd_60 = ( unsigned_t )( TFN_SERIAL_REF_POR ); const unsigned_t TOPPERS_cfg_valueof_svcatr_60 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_60 = ( unsigned_t )( SSZ_SERIAL_REF_POR ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_61 = ( unsigned_t ) ( TDOM_KERNEL );
#line 30 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_61 = 61;
#define SERIAL_RCV_SEM1	(<>)

#line 30 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_61 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_61 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_61 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_62 = ( unsigned_t ) ( TDOM_KERNEL );
#line 31 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_62 = 62;
#define SERIAL_SND_SEM1	(<>)

#line 31 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_62 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_62 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_62 = ( unsigned_t )( 1 ); 
#if TNUM_PORT >= 2
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_63 = ( unsigned_t ) ( TDOM_KERNEL );
#line 33 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_63 = 63;
#define SERIAL_RCV_SEM2	(<>)

#line 33 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_63 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_63 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_63 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_64 = ( unsigned_t ) ( TDOM_KERNEL );
#line 34 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_64 = 64;
#define SERIAL_SND_SEM2	(<>)

#line 34 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_64 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_64 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_64 = ( unsigned_t )( 1 ); 
#endif 

#if TNUM_PORT >= 3
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_65 = ( unsigned_t ) ( TDOM_KERNEL );
#line 37 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_65 = 65;
#define SERIAL_RCV_SEM3	(<>)

#line 37 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_65 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_65 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_65 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_66 = ( unsigned_t ) ( TDOM_KERNEL );
#line 38 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_66 = 66;
#define SERIAL_SND_SEM3	(<>)

#line 38 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_66 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_66 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_66 = ( unsigned_t )( 1 ); 
#endif 

#if TNUM_PORT >= 4
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_67 = ( unsigned_t ) ( TDOM_KERNEL );
#line 41 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_67 = 67;
#define SERIAL_RCV_SEM4	(<>)

#line 41 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_67 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_67 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_67 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_68 = ( unsigned_t ) ( TDOM_KERNEL );
#line 42 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_68 = 68;
#define SERIAL_SND_SEM4	(<>)

#line 42 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_68 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_68 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_68 = ( unsigned_t )( 1 ); 
#endif 

#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 44 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL

/* #include "syssvc/logtask.h" */

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 11 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_69 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_69 = 69;
#define LOGTASK	(<>)

#line 12 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_69 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_69 = ( signed_t )( LOGTASK_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_69 = ( unsigned_t )( LOGTASK_STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_70 = ( unsigned_t ) ( TDOM_KERNEL );
#line 14 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_70 = 70;
const unsigned_t TOPPERS_cfg_valueof_teratr_70 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_71 = ( unsigned_t ) ( TDOM_KERNEL );
#line 15 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_71 = 71;
const char TOPPERS_cfg_valueof_module_71[] = "logtask.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_72 = ( unsigned_t ) ( TDOM_KERNEL );
#line 17 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_72 = 72;
const unsigned_t TOPPERS_cfg_valueof_fncd_72 = ( unsigned_t )( TFN_LOGTASK_FLUSH ); const unsigned_t TOPPERS_cfg_valueof_svcatr_72 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_72 = ( unsigned_t )( SSZ_LOGTASK_FLUSH ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 19 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/syssvc/logtask.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL

/* #include "sample1.h" */

#ifndef TOPPERS_cfg_valueof_DOM1_DEFINED
#define TOPPERS_cfg_valueof_DOM1_DEFINED 1

#line 16 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_DOM1 = DOM1;

#endif
#define TOPPERS_cfg_inside_of_DOM1
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_73 = ( unsigned_t ) ( DOM1 );
#line 17 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_73 = 73;
#define TASK1	(<>)

#line 17 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_73 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_73 = ( signed_t )( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_73 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_74 = ( unsigned_t ) ( DOM1 );
#line 18 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_74 = 74;
const unsigned_t TOPPERS_cfg_valueof_texatr_74 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_75 = ( unsigned_t ) ( DOM1 );
#line 19 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_75 = 75;
const unsigned_t TOPPERS_cfg_valueof_acptn1_75 = ( unsigned_t )( TACP(DOM1)|TACP(DOM2) ); const unsigned_t TOPPERS_cfg_valueof_acptn2_75 = ( unsigned_t )( TACP(DOM1) ); const unsigned_t TOPPERS_cfg_valueof_acptn3_75 = ( unsigned_t )( TACP(DOM1) ); const unsigned_t TOPPERS_cfg_valueof_acptn4_75 = ( unsigned_t )( TACP(DOM1) ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_76 = ( unsigned_t ) ( DOM1 );
#line 20 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_76 = 76;
#define TASK2	(<>)

#line 20 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_76 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_76 = ( signed_t )( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_76 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_77 = ( unsigned_t ) ( DOM1 );
#line 21 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_77 = 77;
const unsigned_t TOPPERS_cfg_valueof_texatr_77 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_DOM1

#line 22 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_DOM1


#ifndef TOPPERS_cfg_valueof_DOM2_DEFINED
#define TOPPERS_cfg_valueof_DOM2_DEFINED 1

#line 23 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_DOM2 = DOM2;

#endif
#define TOPPERS_cfg_inside_of_DOM2

#ifndef TOPPERS_cfg_inside_of_DOM2

#line 24 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_DOM2


#line 25 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_78 = 78;
const unsigned_t TOPPERS_cfg_valueof_notsk_78 = ( unsigned_t )( 3 ); 
#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 26 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_79 = ( unsigned_t ) ( TDOM_KERNEL );
#line 27 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_79 = 79;
#define MAIN_TASK	(<>)

#line 27 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_79 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_79 = ( signed_t )( MAIN_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_79 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_80 = ( unsigned_t ) ( TDOM_KERNEL );
#line 28 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_80 = 80;
#define CYCHDR1	(<>)

#line 28 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_80 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_cyctim_80 = ( unsigned_t )( 2000 ); const unsigned_t TOPPERS_cfg_valueof_cycphs_80 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_81 = ( unsigned_t ) ( TDOM_KERNEL );
#line 29 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_81 = 81;
#define ALMHDR1	(<>)

#line 29 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_almatr_81 = ( unsigned_t )( TA_NULL ); 
#ifdef TOPPERS_SUPPORT_OVRHDR
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_82 = ( unsigned_t ) ( TDOM_KERNEL );
#line 31 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_82 = 82;
const unsigned_t TOPPERS_cfg_valueof_ovratr_82 = ( unsigned_t )( TA_NULL ); 
#endif 

#ifdef CPUEXC1
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_83 = ( unsigned_t ) ( TDOM_KERNEL );
#line 34 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_83 = 83;
const unsigned_t TOPPERS_cfg_valueof_excno_83 = ( unsigned_t )( CPUEXC1 ); const unsigned_t TOPPERS_cfg_valueof_excatr_83 = ( unsigned_t )( TA_NULL ); 
#endif 
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_84 = ( unsigned_t ) ( TDOM_KERNEL );
#line 36 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_84 = 84;
const unsigned_t TOPPERS_cfg_valueof_acptn1_84 = ( unsigned_t )( TACP(DOM1)|TACP(DOM2) ); const unsigned_t TOPPERS_cfg_valueof_acptn2_84 = ( unsigned_t )( TACP(DOM2) ); const unsigned_t TOPPERS_cfg_valueof_acptn3_84 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_84 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_85 = ( unsigned_t ) ( TDOM_KERNEL );
#line 37 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_85 = 85;
const unsigned_t TOPPERS_cfg_valueof_kmmsz_85 = ( unsigned_t )( KMM_SIZE ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 38 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#line 39 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_86 = 86;
const char TOPPERS_cfg_valueof_module_86[] = "sample1.o"; 
#line 40 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_87 = 87;
const char TOPPERS_cfg_valueof_module_87[] = "log_output.o"; 
#line 41 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_88 = 88;
const char TOPPERS_cfg_valueof_module_88[] = "vasyslog.o"; 
#line 42 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_89 = 89;
const char TOPPERS_cfg_valueof_module_89[] = "t_perror.o"; 
#line 43 "G:/MicroFrameworkPK_v4_3/DeviceCode/Targets/OS/Toppers/hrp2/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_90 = 90;
const char TOPPERS_cfg_valueof_module_90[] = "strerror.o"; 
#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_DOM1
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_DOM2
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

