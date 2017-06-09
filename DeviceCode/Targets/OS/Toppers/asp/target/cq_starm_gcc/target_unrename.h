/* This file is generated from target_rename.def by genrename. */

/* This file is included only when target_rename.h has been included. */
#ifdef TOPPERS_TARGET_RENAME_H
#undef TOPPERS_TARGET_RENAME_H


/*
 *  target_config.c, target_support.S
 */
#undef log_dsp_enter
#undef log_dsp_leave
#undef log_inh_enter
#undef log_inh_leave
#undef log_exc_enter
#undef log_exc_leave

#ifdef TOPPERS_LABEL_ASM

/*
 *  target_config.c, target_support.S
 */
#undef _log_dsp_enter
#undef _log_dsp_leave
#undef _log_inh_enter
#undef _log_inh_leave
#undef _log_exc_enter
#undef _log_exc_leave

#endif /* TOPPERS_LABEL_ASM */

#ifdef __GNUC__
#include "arm_m_gcc/common/core_unrename.h"
#else
#include "arm_m_msvc/common/core_unrename.h"
#endif

#endif /* TOPPERS_TARGET_RENAME_H */
