#ifndef TOPPERS_TARGET_KERNEL_H
#define TOPPERS_TARGET_KERNEL_H

#define TOPPERS_TARGET_SUPPORT_DIS_INT
#define TOPPERS_TARGET_SUPPORT_ENA_INT
#define TOPPERS_TARGET_SUPPORT_GET_UTM
#define TOPPERS_TARGET_SUPPORT_OVRHDR 

#ifndef TMIN_INTPRI
#define TMIN_INTPRI     (-6)    
#endif /* TMIN_INTPRI */

#define TMAX_INTPRI     (-1)    

#ifndef TIC_NUME
#define TIC_NUME        10U     
#define TIC_DENO        1U      
#endif /* TIC_NUME */

#endif /* TOPPERS_TARGET_KERNEL_H */