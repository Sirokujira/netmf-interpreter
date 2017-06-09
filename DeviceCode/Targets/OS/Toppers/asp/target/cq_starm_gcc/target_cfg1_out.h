/*
 *  @(#) $Id: target_cfg1_out.h 107 2012-09-10 12:15:27Z nagasima $
 */

/*
 *		cfg1_out.cをリンクするために必要なスタブの定義
 */

STK_T *const	_kernel_istkpt = 0x00;

/*
 *  コア依存のスタブの定義 
 */
#ifdef __GNUC__
#include "arm_m_gcc/common/core_cfg1_out.h"
#else
#include "arm_m_msvc/common/core_cfg1_out.h"
#endif
