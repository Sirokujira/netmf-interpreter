#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>

#include "netmf.h"

// NetMF 用
// #include <tinyclr_application.h>
// #include <tinyhal.h>

// netmf の実行?

/*
*  並行実行されるタスク(NETMF)
 */
void task_netmf(intptr_t exinf)
{
	/*
	extern void ApplicationEntryPoint(void);
	void (*volatile fp)(void) = ApplicationEntryPoint;

	// ApplicationEntryPoint を呼出し（0 でない場合）
	// で一旦volatile指定のあるfpに代入する． 
	// if (fp != 0) {
	// 	(*fp)();
	// }
	*/
}

