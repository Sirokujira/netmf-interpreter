/* Configured with [-s -c -v -obj -lj -cpu windows -system msvc ] */

#include "kernel_cfg.h"
#include "kernel_id.h"

#if TKERNEL_PRVER >= 0x1040
#define CFG_INTHDR_ENTRY(inthdr) INTHDR_ENTRY(inthdr)
#define CFG_EXCHDR_ENTRY(exchdr) EXCHDR_ENTRY(exchdr)
#define CFG_INT_ENTRY(inthdr) INT_ENTRY(inthdr)
#define CFG_EXC_ENTRY(exchdr) EXC_ENTRY(exchdr)
#else
#error "This configuration file has no compatibility with TOPPERS/JSP rel 1.3 or earlier."
#endif

#ifndef __EMPTY_LABEL
#define __EMPTY_LABEL(x,y) x y[0]
#endif

#if TKERNEL_PRID != 0x0001u /* TOPPERS/JSP */
#error "You can not use this configuration file without TOPPERS/JSP"
#endif

	/* ユーザ定義のインクルードファイル*/
#include "sample1.h"
#include "hw_timer.h"
#include "timer.h"
#include "hw_serial.h"
#include "serial.h"
#include "logtask.h"


	/* オブジェクト初期化ブロック [task] */

#define TNUM_TSKID 5

const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);

static __STK_UNIT __stack_TASK1[__TCOUNT_STK_UNIT(8192)];
static __STK_UNIT __stack_TASK2[__TCOUNT_STK_UNIT(8192)];
static __STK_UNIT __stack_TASK3[__TCOUNT_STK_UNIT(8192)];
static __STK_UNIT __stack_MAIN_TASK[__TCOUNT_STK_UNIT(8192)];
static __STK_UNIT __stack_LOGTASK[__TCOUNT_STK_UNIT(LOGTASK_STACK_SIZE)];

const TINIB _kernel_tinib_table[TNUM_TSKID] = {
	{TA_HLNG, (VP_INT)(( VP_INT ) 1), (FP)(task), INT_PRIORITY(10), __TROUND_STK_UNIT(8192), __stack_TASK1, TA_HLNG, (FP)(tex_routine)},
	{TA_HLNG, (VP_INT)(( VP_INT ) 2), (FP)(task), INT_PRIORITY(10), __TROUND_STK_UNIT(8192), __stack_TASK2, TA_HLNG, (FP)(tex_routine)},
	{TA_HLNG, (VP_INT)(( VP_INT ) 3), (FP)(task), INT_PRIORITY(10), __TROUND_STK_UNIT(8192), __stack_TASK3, TA_HLNG, (FP)(tex_routine)},
	{TA_HLNG | TA_ACT, (VP_INT)(0), (FP)(main_task), INT_PRIORITY(5), __TROUND_STK_UNIT(8192), __stack_MAIN_TASK, TA_NULL, (FP)(NULL)},
	{TA_HLNG | TA_ACT, (VP_INT)(( VP_INT ) 1), (FP)(logtask), INT_PRIORITY(LOGTASK_PRIORITY), __TROUND_STK_UNIT(LOGTASK_STACK_SIZE), __stack_LOGTASK, TA_NULL, (FP)(NULL)}
};

const ID _kernel_torder_table[TNUM_TSKID] = {1,2,3,4,5};

TCB _kernel_tcb_table[TNUM_TSKID];


	/* オブジェクト初期化ブロック [semaphore] */

#define TNUM_SEMID 2

const ID _kernel_tmax_semid = (TMIN_SEMID + TNUM_SEMID - 1);

const SEMINIB _kernel_seminib_table[TNUM_SEMID] = {
	{TA_TPRI, 0, 1},
	{TA_TPRI, 1, 1}
};

SEMCB _kernel_semcb_table[TNUM_SEMID];


	/* オブジェクト初期化ブロック [eventflag] */

#define TNUM_FLGID 0

const ID _kernel_tmax_flgid = (TMIN_FLGID + TNUM_FLGID - 1);

__EMPTY_LABEL(const FLGINIB, _kernel_flginib_table);
__EMPTY_LABEL(FLGCB, _kernel_flgcb_table);


	/* オブジェクト初期化ブロック [dataqueue] */

#define TNUM_DTQID 0

const ID _kernel_tmax_dtqid = (TMIN_DTQID + TNUM_DTQID - 1);

__EMPTY_LABEL(const DTQINIB, _kernel_dtqinib_table);
__EMPTY_LABEL(DTQCB, _kernel_dtqcb_table);


	/* オブジェクト初期化ブロック [mailbox] */

#define TNUM_MBXID 0

const ID _kernel_tmax_mbxid = (TMIN_MBXID + TNUM_MBXID - 1);

__EMPTY_LABEL(const MBXINIB, _kernel_mbxinib_table);
__EMPTY_LABEL(MBXCB, _kernel_mbxcb_table);


	/* オブジェクト初期化ブロック [mempfix] */

#define TNUM_MPFID 0

const ID _kernel_tmax_mpfid = (TMIN_MPFID + TNUM_MPFID - 1);

__EMPTY_LABEL(const MPFINIB, _kernel_mpfinib_table);
__EMPTY_LABEL(MPFCB, _kernel_mpfcb_table);


	/* オブジェクト初期化ブロック [cyclic] */

#define TNUM_CYCID 1

const ID _kernel_tmax_cycid = (TMIN_CYCID + TNUM_CYCID - 1);

const CYCINIB _kernel_cycinib_table[TNUM_CYCID] = {
	{TA_HLNG,0,(FP)(cyclic_handler),2000,0}
};

CYCCB _kernel_cyccb_table[TNUM_CYCID];


	/* オブジェクト初期化ブロック [interrupt] */

#define TNUM_INHNO 2

const UINT _kernel_tnum_inhno = TNUM_INHNO;

CFG_INTHDR_ENTRY(timer_handler);
CFG_INTHDR_ENTRY(sio_handler);

const INHINIB _kernel_inhinib_table[TNUM_INHNO] = {
	{4,TA_HLNG,(FP)CFG_INT_ENTRY(timer_handler)},
	{INHNO_SERIAL,TA_HLNG,(FP)CFG_INT_ENTRY(sio_handler)}
};


	/* オブジェクト初期化ブロック [exception] */

#define TNUM_EXCNO 0

const UINT _kernel_tnum_excno = TNUM_EXCNO;

__EMPTY_LABEL(const EXCINIB, _kernel_excinib_table);
	/* 初期化ハンドラ起動ルーチン */

void
_kernel_call_inirtn(void)
{
	timer_initialize( (VP_INT)(0) );
	serial_initialize( (VP_INT)(0) );
}

void
_kernel_call_terrtn(void)
{
	timer_terminate( (VP_INT)(0) );
}

	/* オブジェクト初期化ルーチン */

void
_kernel_object_initialize(void)
{
	_kernel_task_initialize();
	_kernel_semaphore_initialize();
	_kernel_cyclic_initialize();
	_kernel_interrupt_initialize();
}

TMEVTN   _kernel_tmevt_heap[TNUM_TSKID + TNUM_CYCID];

	/* カーネルチェッカ用変数 */
const UW _checker_magic_number = 0x01234567;

