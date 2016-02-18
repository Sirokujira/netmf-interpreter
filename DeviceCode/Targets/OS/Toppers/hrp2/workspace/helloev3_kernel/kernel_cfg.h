/* kernel_cfg.h */
#ifndef TOPPERS_KERNEL_CFG_H
#define TOPPERS_KERNEL_CFG_H

#define TNUM_DOMID	1
#define TNUM_TSKID	58
#define TNUM_SEMID	28
#define TNUM_FLGID	19
#define TNUM_DTQID	0
#define TNUM_PDQID	0
#define TNUM_MTXID	3
#define TNUM_MPFID	0
#define TNUM_CYCID	18
#define TNUM_ALMID	2
#define TNUM_ISRID	1

#define TMAX_FNCD	TFN_FILESYS_CLOSEDIR

#define TDOM_APP	1
#define LOGTASK	1
#define BRICK_BTN_TSK	2
#define LCD_REFRESH_TSK	3
#define CONSOLE_BTN_TSK	4
#define BT_TSK	5
#define BT_QOS_TSK	6
#define EV3_INIT_TASK	7
#define PLATFORM_BUSY_TASK	8
#define APP_INIT_TASK	9
#define MAIN_TASK	10
#define BT_SND_BUF_SEM	1
#define SERIAL_RCV_SEM1	2
#define SERIAL_SND_SEM1	3
#define SERIAL_RCV_SEM2	4
#define SERIAL_SND_SEM2	5
#define SERIAL_RCV_SEM3	6
#define SERIAL_SND_SEM3	7
#define FATFS_SEM	8
#define LCD_DMA_DONE_SEM	9
#define SUART1_SEM	10
#define SUART2_SEM	11
#define SND_DEV_SEM	12
#define BTN_CLICK_FLG	1
#define CONSOLE_BTN_CLICK_FLG	2
#define MMCSD_ISR_FLG	3
#define MMCSD_RW_MTX	1
#define EV3RT_CONSOLE_MTX	2
#define EV3RT_CONSOLE_LOG_MTX	3
#define BT_SIO_CYC	1
#define BRICK_BTN_CYC	2
#define BT_RCV_ALM	1
#define SND_STOP_ALM	2

#endif /* TOPPERS_KERNEL_CFG_H */

