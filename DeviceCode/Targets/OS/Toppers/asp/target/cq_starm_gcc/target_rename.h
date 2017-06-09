/* This file is generated from target_rename.def by genrename. */

#ifndef TOPPERS_TARGET_RENAME_H
#define TOPPERS_TARGET_RENAME_H


#ifdef TOPPERS_LABEL_ASM


#endif /* TOPPERS_LABEL_ASM */

#ifdef __GNUC__
#include "arm_m_gcc/common/core_rename.h"
#else
#include "arm_m_msvc/common/core_rename.h"
#endif

/*
 *  target_config.c, target_support.S
 */
#define log_dsp_enter				_kernel_log_dsp_enter
#define log_dsp_leave				_kernel_log_dsp_leave
#define log_inh_enter				_kernel_log_inh_enter
#define log_inh_leave				_kernel_log_inh_leave
#define log_exc_enter				_kernel_log_exc_enter
#define log_exc_leave				_kernel_log_exc_leave

#ifdef TOPPERS_LABEL_ASM

/*
 *  target_config.c, target_support.S
 */
#define _log_dsp_enter				__kernel_log_dsp_enter
#define _log_dsp_leave				__kernel_log_dsp_leave
#define _log_inh_enter				__kernel_log_inh_enter
#define _log_inh_leave				__kernel_log_inh_leave
#define _log_exc_enter				__kernel_log_exc_enter
#define _log_exc_leave				__kernel_log_exc_leave

#endif /* TOPPERS_LABEL_ASM */

#endif /* TOPPERS_TARGET_RENAME_H */
