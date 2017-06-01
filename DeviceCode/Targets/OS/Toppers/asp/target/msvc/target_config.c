/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2006-2011 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  @(#) $Id: target_config.c 2728 2015-12-30 01:46:11Z ertl-honda $
 */

/*
 *		ターゲット依存モジュール（Windows用）
 */

#include "kernel_impl.h"
#include "task.h"

/*
 *  トレースログマクロのデフォルト定義
 */
#ifndef LOG_DSP_ENTER
#define LOG_DSP_ENTER(p_tcb)
#endif /* LOG_DSP_ENTER */

#ifndef LOG_DSP_LEAVE
#define LOG_DSP_LEAVE(p_tcb)
#endif /* LOG_DSP_LEAVE */

/*
 *  TMIN_INTPRIの範囲のチェック
 */
#if (TMIN_INTPRI > -1) || (-6 > TMIN_INTPRI)
#error TMIN_INTPRI out of range.
#endif /* (TMIN_INTPRI > -1) || (-6 > TMIN_INTPRI) */

/*
 *  割込みロック／CPUロックへの移行でマスクするシグナルを保持する変数
 */
// sigset_t	sigmask_intlock;	/* 割込みロックでマスクするシグナル */
// sigset_t	sigmask_cpulock;	/* CPUロックでマスクするシグナル */

/*
 *  CPUロックフラグ実現のための変数
 */
volatile bool_t		lock_flag;		/* CPUロックフラグを表す変数 */
// volatile sigset_t	saved_sigmask;	/* シグナルマスクを保存する変数 */

/*
 *  割込み優先度マスク実現のための変数
 */
volatile PRI		ipm_value;		/* 割込み優先度マスクを表す変数 */

/*
 *  割込み要求禁止フラグ実現のための変数
 */
// volatile sigset_t	sigmask_disint;	/* 個別にマスクしているシグナル */

volatile uint32_t	saved_iipm;		/* 割込み優先度マスクを保存する変数 */

/*
 *  ディスパッチャ本体の割込み待ち中であることを示す変数
 */
static bool_t	dispatcher_idle;	/* 割込み待ち中である */

/*
 *  ディスパッチャ本体
 *
 *  LOG_DSP_ENTERとLOG_DSP_LEAVEを，dispatcherに入れず，これを呼び出す
 *  関数の側に入れている理由は次の通り．LOG_DSP_ENTERは，ディスパッチの
 *  動作開始時（mainから呼ばれた時）には，呼び出してはならないため，
 *  dispatcherに入れることができない．LOG_DSP_LEAVEは，切換え後のタスク
 *  のスタックで呼び出さなければならないため，_longjmpを実行した後に呼
 *  び出す必要があり，dispatcherを呼び出す関数の側に入れなければならな
 *  い．
 */
static void
dispatcher(void)
{
	// Windows 用に書き直し
	// sigset_t	sigmask;
	// 
	// while ((p_runtsk = p_schedtsk) == NULL) {
	// 	/*
	// 	 *  CPUロック状態を解除する準備をする．sigmaskには，CPUロック状
	// 	 *  態に移行する前のシグナルマスクを取り出す．
	// 	 */
	// 	lock_flag = false;
	// 	sigassignset(&sigmask, &saved_sigmask);
	// 	do {
	// 		/*
	// 		 *  割込み待ちの間に発生した割込みハンドラではSIGUSR2を
	// 		 *  raiseしないように，dispatcher_idleをtrueにする．
	// 		 */
	// 		dispatcher_idle = true;
	// 		sigsuspend(&sigmask);			/* 割込み待ち */
	// 		dispatcher_idle = false;
	// 	} while (!reqflg);
	// 	reqflg = false;
	// 
	// 	/*
	// 	 *  CPUロック状態に戻す．割込み待ちの間に実行した割込みハンドラ
	// 	 *  により，saved_sigmaskは書き換わる可能性があるため，元の値に
	// 	 *  戻す必要がある．
	// 	 */
	// 	sigassignset(&saved_sigmask, &sigmask);
	// 	lock_flag = true;
	// }
	// _longjmp(p_runtsk->tskctxb.env, 1);
}

/*
 *  最高優先順位タスクへのディスパッチ
 */
void
dispatch(void)
{
	// Windows 用に書き直し
#ifdef TOPPERS_SUPPORT_OVRHDR
	ovrtimer_stop();					/* オーバランタイマの停止 */
#endif /* TOPPERS_SUPPORT_OVRHDR */
	// if (_setjmp(p_runtsk->tskctxb.env) == 0) {
	// 	LOG_DSP_ENTER(p_runtsk);
	// 	dispatcher();
	// 	assert(0);
	// }
	// LOG_DSP_LEAVE(p_runtsk);
#ifdef TOPPERS_SUPPORT_OVRHDR
	ovrtimer_start();					/* オーバランタイマの動作開始 */
#endif /* TOPPERS_SUPPORT_OVRHDR */
	// calltex();
}

/*
 *  最高優先順位タスクへのディスパッチ（シグナルハンドラ用）
 */
static void
dispatch_handler(int sig, struct __siginfo *p_info, void *p_ctx)
{
#ifdef TOPPERS_SUPPORT_OVRHDR
	/*
	 *  オーバランハンドラ機能をサポートする場合には，dispatch_handler
	 *  は必ず起動される．ディスパッチが必要ない場合には，オーバランハ
	 *  ンドラの動作開始のみを行う．
	 */
	if (!(!dispatcher_idle && reqflg)) {
		ovrtimer_start();				/* オーバランタイマの動作開始 */
		return;
	}
	reqflg = false;
#endif /* TOPPERS_SUPPORT_OVRHDR */
	// Windows 用に書き直し
	// /*
	//  *  シグナルハンドラの実行開始前のシグナルマスクをsaved_sigmaskに代
	//  *  入し，CPUロック状態に移行する．
	//  */
	// sigassignset(&saved_sigmask, &(((ucontext_t *) p_ctx)->uc_sigmask));
	// lock_flag = true;
	// 
	// if (dspflg && p_runtsk != p_schedtsk) {
	// 	if (_setjmp(p_runtsk->tskctxb.env) == 0) {
	// 		LOG_DSP_ENTER(p_runtsk);
	// 		dispatcher();
	// 		assert(0);
	// 	}
	// 	LOG_DSP_LEAVE(p_runtsk);
	// }
#ifdef TOPPERS_SUPPORT_OVRHDR
	ovrtimer_start();					/* オーバランタイマの動作開始 */
#endif /* TOPPERS_SUPPORT_OVRHDR */
	// calltex();

	// /*
	//  *  シグナルハンドラからのリターン後のシグナルマスクがsaved_sigmask
	//  *  になるように設定し，CPUロック状態を解除する．
	//  */
	// lock_flag = false;
	// sigassignset(&(((ucontext_t *) p_ctx)->uc_sigmask), &saved_sigmask);
}

/*
 *  現在のコンテキストを捨ててディスパッチ
 */
void
exit_and_dispatch(void)
{
	// LOG_DSP_ENTER(p_runtsk);
	// dispatcher();
	// assert(0);
}

/*
 *  割込みハンドラ出口処理
 *
 *  割込みハンドラ中では，カーネル管理の割込みを禁止しているため，出口
 *  処理で割込みを禁止する必要はない．
 */
void
ret_int(void)
{
#ifndef TOPPERS_SUPPORT_OVRHDR
	/*
	 *  ディスパッチャの起動を要求する．
	 *
	 *  reqflgをチェックした直後に割込みが入っても，入った側の割込みで
	 *  タスクディスパッチャの起動を要求するため，reqflgをチェックする
	 *  前に割込みを禁止する必要がない．
	 */
	// if (!dispatcher_idle && reqflg) {
	// 	reqflg = false;
	// 	raise(SIGUSR2);
	// }
#else /* TOPPERS_SUPPORT_OVRHDR */
	/*
	 *  オーバランハンドラ機能をサポートする場合には，オーバランタイマ
	 *  を動作開始するために，dispatch_handlerを必ず起動する．
	 */
	// raise(SIGUSR2);
#endif /* TOPPERS_SUPPORT_OVRHDR */
}

/*
 *  CPU例外ハンドラ出口処理
 */
void
ret_exc(void)
{
#ifndef TOPPERS_SUPPORT_OVRHDR
	/*
	 *  ディスパッチャの起動を要求する．
	 *
	 *  reqflgをチェックした直後に割込みが入っても，入った側の割込みで
	 *  タスクディスパッチャの起動を要求するため，reqflgをチェックする
	 *  前に割込みを禁止する必要がない．
	 */
	// if (!dispatcher_idle && reqflg) {
	// 	reqflg = false;
	// 	raise(SIGUSR2);
	// }
#else /* TOPPERS_SUPPORT_OVRHDR */
	/*
	 *  オーバランハンドラ機能をサポートする場合には，オーバランタイマ
	 *  を動作開始するために，dispatch_handlerを必ず起動する．
	 */
	// raise(SIGUSR2);
#endif /* TOPPERS_SUPPORT_OVRHDR */
}

/*
 *  カーネルの終了処理の呼出し
 */
void
call_exit_kernel(void)
{
	// Windows 用に書き直し
}

/*
 *  タスク開始時処理
 */
void
start_r(void)
{
#ifdef TOPPERS_SUPPORT_OVRHDR
	ovrtimer_start();					/* オーバランタイマの動作開始 */
#endif /* TOPPERS_SUPPORT_OVRHDR */
	t_unlock_cpu();
	(*(p_runtsk->p_tinib->task))(p_runtsk->p_tinib->exinf);
	(void) ext_tsk();
	assert(0);
}

/****************************************************************************
*
* 割り込みスレッドへのメッセージ.
*
****************************************************************************/
#define	WM_SYSTEM_EXIT	(WM_USER + 1)		//!< システムの終了.
#define	WM_INTRRUPT_REQ	(WM_USER + 2)		//!< 割り込み要求.

/****************************************************************************
*
* ローカル関数定義.
*
****************************************************************************/
static unsigned int __stdcall	IntrTask(void* arg);
static void			CallIntrruptHandler(INT no);

/****************************************************************************
*
* ローカル変数定義.
*
****************************************************************************/
static WIHDR		*ObjList;			//!< 割り込みハンドラ･リストのポインタ.
static HANDLE		IntrThread;			//!< 割り込みスレッドのハンドル.
static DWORD		IntrTid;			//!< 割り込みスレッドの識別子.
static BOOL			CpuLockFlg;			//!< TRUE = CPUロック中.

/****************************************************************************
*
* 構造体定義.
*
****************************************************************************/


/*
 *  ターゲット依存の初期化
 */
void
target_initialize(void)
{
	// Windows 用処理
	unsigned int tid;

	ObjList = NULL;
	IntrThread = NULL;
	IntrTid = 0;
	CpuLockFlg = FALSE;

	//! 割り込みスレッドを起動する.
	IntrThread = (HANDLE)_beginthreadex(NULL, 0, &IntrTask, NULL, 0, &tid);

	//! タスクの優先度を設定する.
	SetThreadPriority(IntrThread, THREAD_PRIORITY_HIGHEST);
}

/****************************************************************************/
/*!
*	@brief	割り込みタスク.
*	@param	[in]	arg		タスクリソース構造体のポインタ.
*	@retval	常に0を返す.
*/
static unsigned __stdcall IntrTask(void* arg)
{
	MSG	msg;

	//! スレッド識別子を取得する.
	IntrTid = GetCurrentThreadId();

	//! メッセージループ.
	while (GetMessage(&msg, NULL, 0, 0)){

		//! システムの終了の場合はメッセージループを抜ける.
		if (msg.message == WM_SYSTEM_EXIT){
			break;
		}
		switch (msg.message){
		case WM_INTRRUPT_REQ:
			CallIntrruptHandler((INT)msg.wParam);
			break;
		}
	}
	_endthreadex(0);
	return 0;
}

/****************************************************************************/
/*!
*	@brief	割り込みハンドラを呼び出す.
*	@param	[in]	no		割り込みハンドラ番号.
*	@retval	なし.
*/
static void	CallIntrruptHandler(INT no)
{
	// wi_CommonLock();
	do {
		FP			intr_adr;
		ER			ercd;
		WIINTOBJ	*p;

		//! 割り込みハンドラ構造体を取り出す.
		// p = (WIINTOBJ *)wi_FindObject(no, TMAX_MAXINT, ObjList, &ercd);
		if (!p)
		{
			break;
		}
		
		//! 割り込みエントリ･アドレスがない場合は呼び出さない.
		if (!p->IntrAdr)
		{
			break;
		}
		//! 割り込み禁止の場合は呼び出さない.
		// if (!p->Enabled || wi_IsCPULock()){
		// 	p->IntrCnt++;
		// 	break;
		// }
		p->IntrCnt = 0;

		intr_adr = p->IntrAdr;

		// wi_CommonUnlock();

		//! 割り込みハンドラを呼び出す.
		// intr_adr();
		return;

	} while (FALSE);

	// wi_CommonUnlock();
}

/* End of file */

// 

/*
 *  ターゲット依存の終了処理
 */
void
target_exit(void)
{
	/*
	 *  プロセスの終了処理
	 */
	// exit(0);

	WIHDR		*next_ptr;
	WIINTOBJ	*p;

	//! システム管理スレッドを終了させる.
	if (IntrThread){
		//! 割り込みスレッドに終了を通知する.
		PostThreadMessage(IntrTid, WM_SYSTEM_EXIT, 0, 0);

		//! - スレッドが停止するのを確認する.
		// wi_DormantThread(IntrThread, 1000);

		//! - 割り込みスレッドのハンドルを解放する.
		CloseHandle(IntrThread);
	}
	p = (WIINTOBJ *)ObjList;
	while (p){
		next_ptr = p->Hdr.Next;

		//! 割り込みハンドラ構造体を解放する.
		// SAFE_RELEASE(p);

		//! 次の割り込みハンドラ構造体を取り出す.
		p = (WIINTOBJ *)next_ptr;
	}
}

/*
 *  システムログの低レベル出力のための文字出力
 */
void
target_fput_log(char c)
{
	// write(STDERR_FILENO, &c, 1);
}

/*
 *  割込み管理機能の初期化
 */
void
initialize_interrupt(void)
{
	// Windows 用処理
}

/*
 *  メイン関数
 */
int
main()
{
	// sigset_t			sigmask;
	// stack_t				ss;
	// struct sigaction	sigact;
	// 
	// /*
	//  *  SIGUSR2以外のすべてのシグナルをマスク
	//  */
	// sigfillset(&sigmask);
	// sigdelset(&sigmask, SIGUSR2);
	// sigprocmask(SIG_BLOCK, &sigmask, NULL);
	// 
	// /*
	//  *  シグナルスタック（非タスクコンテキスト用のスタック）の設定
	//  */
	// ss.ss_sp = (char *)(istk);
	// ss.ss_size = (int)(istksz);
	// ss.ss_flags = 0;
	// sigaltstack(&ss, NULL);
	// 
	// /*
	//  *  SIGUSR2のシグナルハンドラにsta_kerを登録
	//  */
	// sigact.sa_handler = (void (*)(int)) sta_ker;
	// sigact.sa_flags = SA_ONSTACK;
	// sigemptyset(&(sigact.sa_mask));
	// sigaction(SIGUSR2, &sigact, NULL);
	// 
	// /*
	//  *  sta_kerの呼出し
	//  */
	// raise(SIGUSR2);
	// 
	// /*
	//  *  ディスパッチャの動作開始
	//  *
	//  *  target_initializeで，lock_flagをtrueに，ipm_valueをTIPM_ENAALL
	//  *  に初期化しているため，set_sigmaskを呼び出してシグナルマスクと
	//  *  saved_sigmaskを設定することで，CPUロック状態・（モデル上の）割
	//  *  込み優先度マスクがTIPM_ENAALLの状態になる．
	//  *
	//  *  また，initialize_taskでdisdspをfalseに初期化しているため，ディ
	//  *  スパッチ許可状態になっている．
	//  */
	// set_sigmask();
	// dispatcher();
	// assert(0);
	return(0);
}

/*
 *  カーネルの割り付けるメモリ領域の管理
 *
 *  TLSF（オープンソースのメモリ管理ライブラリ）を用いて実現．
 */
#ifdef TOPPERS_SUPPORT_DYNAMIC_CRE

#include "tlsf.h"

static bool_t	tlsf_initialized = false;

void
initialize_kmm(void)
{
	if (init_memory_pool(kmmsz, kmm) >= 0) {
		tlsf_initialized = true;
	}
}

void *
kernel_malloc(SIZE size)
{
	if (tlsf_initialized) {
		return(malloc_ex(size, kmm));
	}
	else {
		return(NULL);
	}
}

void
kernel_free(void *ptr)
{
	if (tlsf_initialized) {
		free_ex(ptr, kmm);
	}
}

#endif /* TOPPERS_SUPPORT_DYNAMIC_CRE */
