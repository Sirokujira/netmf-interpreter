{
	"TimeScale" :"us",
	"TimeRadix" :10,
	"ConvertRules"   :["asp"],
	"VisualizeRules" :["toppers","asp"],
	"ResourceHeaders":["asp"],
	"Resources":
	{
		"CurrentContext":{
			"Type":"Context",
			"Attributes":
			{
				"name"    : "None"
			}
		},
		"LOGTASK":{
			"Type":"Task",
			"Attributes":
			{
				"id"    :1,
				"atr"   :"TA_ACT",
				"pri"   :3,
				"exinf" :"LOGTASK_PORTID",
				"task"  :"logtask_main",
				"stksz" :1024,
				"stk"   :"NULL",
				"state" :"RUNNABLE"
			}
		},
		"TASK1":{
			"Type":"Task",
			"Attributes":
			{
				"id"    :2,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"1",
				"task"  :"task",
				"stksz" :1024,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"TASK2":{
			"Type":"Task",
			"Attributes":
			{
				"id"    :3,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"2",
				"task"  :"task",
				"stksz" :1024,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"TASK3":{
			"Type":"Task",
			"Attributes":
			{
				"id"    :4,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"3",
				"task"  :"task",
				"stksz" :1024,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"MAIN_TASK":{
			"Type":"Task",
			"Attributes":
			{
				"id"    :5,
				"atr"   :"TA_ACT",
				"pri"   :5,
				"exinf" :"0",
				"task"  :"main_task",
				"stksz" :1024,
				"stk"   :"NULL",
				"state" :"RUNNABLE"
			}
		},
		"INH_INHNO_TIMER_target_timer_handler":{
			"Type":"InterruptHandler",
			"Attributes":
			{
				"id"    :15,
				"state"    : "DORMANT"
			}
		},
		"INH_53__kernel_inthdr_53":{
			"Type":"InterruptHandler",
			"Attributes":
			{
				"id"    :53,
				"state"    : "DORMANT"
			}
		},
		"ISR_INTNO_SIO_sio_isr_SIO_PORTID":{
			"Type":"InterruptServiceRoutine",
			"Attributes":
			{
				"id"    :53,
				"state"    : "DORMANT"
			}
		},
		"CYCHDR1":{
			"Type":"CyclicHandler",
			"Attributes":
			{
				"id"    :1,
				"state"    : "DORMANT"
			}
		},
		"ALMHDR1":{
			"Type":"AlarmHandler",
			"Attributes":
			{
				"id"    :1,
				"state"    : "DORMANT"
			}
		},
		"CPUEXC1":{
			"Type":"CPUExceptionHandler",
			"Attributes":
			{
				"id"    :6,
				"state"    : "DORMANT"
			}
		},
		"TASK_TEX":{
			"Type":"TaskExceptionRoutine",
			"Attributes":
			{
				"state"    : "DORMANT"
			}
		}
	}
}

