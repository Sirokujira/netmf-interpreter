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
		"MAIN_TASK":{
			"Type":"Task",
			"Attributes":
			{
				"id"    :1,
				"atr"   :"TA_ACT",
				"pri"   :5,
				"exinf" :"0",
				"task"  :"dummy_task",
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
,
,
,
		"TASK_TEX":{
			"Type":"TaskExceptionRoutine",
			"Attributes":
			{
				"state"    : "DORMANT"
			}
		}
	}
}

