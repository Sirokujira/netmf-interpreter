/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 呼び口関数 #_TCPF_#
 * call port: cTECS signature: sKernel context:task 
 *   ER             cTECS_sleep( );
 *   ER             cTECS_sleepTimeout( TMO timeout );
 *   ER             cTECS_delay( RELTIM delayTime );
 *   ER             cTECS_exitTask( );
 *   ER             cTECS_getTaskId( ID* p_taskId );
 *   ER             cTECS_rotateReadyQueue( PRI taskPriority );
 *   ER             cTECS_getTime( SYSTIM* p_systemTime );
 *   ER             cTECS_getMicroTime( SYSUTM* p_systemMicroTime );
 *   ER             cTECS_lockCpu( );
 *   ER             cTECS_unlockCpu( );
 *   ER             cTECS_disableDispatch( );
 *   ER             cTECS_enableDispatch( );
 *   ER             cTECS_disableTaskException( );
 *   ER             cTECS_enableTaskException( );
 *   ER             cTECS_changeInterruptPriorityMask( PRI interruptPriority );
 *   ER             cTECS_getInterruptPriorityMask( PRI* p_interruptPriority );
 *   ER             cTECS_exitKernel( );
 *   bool_t         cTECS_senseContext( );
 *   bool_t         cTECS_senseLock( );
 *   bool_t         cTECS_senseDispatch( );
 *   bool_t         cTECS_senseDispatchPendingState( );
 *   bool_t         cTECS_senseKernel( );
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "nMruby_tsKernel_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

/* MBP: MrubyBridgePlugin: MBP000 */
#include "mruby.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/string.h"
#include "TECSPointer.h"
#include "TECSStruct.h"

#if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#ifndef NULL
#define NULL 0
#endif

/* RData MBP001 */
static void 
tsKernel_free( mrb_state *mrb, void *p )
{
	if( p )
		(void)mrb_free( mrb, p );
}

/* RData MBP002 */
struct mrb_data_type data_type_tsKernel =
{
	"tsKernel",
	tsKernel_free
};

/* RData MBP003 */
struct tecs_tsKernel {
    CELLCB  *cbp;
};

/* name_to_cbp MBP010 */
const struct name_to_cbp_tsKernel {
    char   *name;    /* Cell Name */
    CELLCB *cbp;
} Name_to_cbp_tsKernel[] = {
	{ "BridgeKernel", NULL },
	{ 0, 0 },
};


/* MBP100 */
mrb_value
MrubyBridge_tsKernel_initialize( mrb_state *mrb, mrb_value self)
{
	mrb_value	name;
	struct tecs_tsKernel *tecs_cb;
	const struct name_to_cbp_tsKernel *ntc;

	/* set DATA_TYPE earlier to avoid SEGV */
	DATA_TYPE( self ) = &data_type_tsKernel;

	mrb_get_args(mrb, "o", &name );
	if( mrb_type( name ) != MRB_TT_STRING ){
		mrb_raise(mrb, E_NAME_ERROR, "cell name not string");
	}
	for( ntc = &Name_to_cbp_tsKernel[0]; ntc->name != NULL; ntc++ ){
		if( strcmp( ntc->name, RSTRING_PTR( name ) ) == 0 )
			break;
	}
	if( ntc->name == 0 ){
		mrb_raise(mrb, E_ARGUMENT_ERROR, "cell not found");
	}
	tecs_cb = (struct tecs_tsKernel *)mrb_malloc(mrb, sizeof(struct tecs_tsKernel) );
	tecs_cb->cbp = ntc->cbp;
	DATA_PTR( self ) = (void *)tecs_cb;

	return self;
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_sleep( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_sleep(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_sleepTimeout( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_int	mrb_timeout;
	TMO	timeout;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "i", &mrb_timeout );
	/* convert mrb to C (MBP112) */
	VALCHECK_Int( mrb, mrb_timeout );
	timeout = (TMO)mrb_timeout;
	/* calling target (MBP120) */
	ret_val = cTECS_sleepTimeout( timeout );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_delay( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_int	mrb_delayTime;
	RELTIM	delayTime;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "i", &mrb_delayTime );
	/* convert mrb to C (MBP112) */
	VALCHECK_UInt( mrb, mrb_delayTime );
	delayTime = (RELTIM)mrb_delayTime;
	/* calling target (MBP120) */
	ret_val = cTECS_delay( delayTime );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_exitTask( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_exitTask(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_getTaskId( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_value	mrb_p_taskId;
	ID*	p_taskId;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "o", &mrb_p_taskId );
	/* convert mrb to C for pointer types (MBP113) */
	p_taskId = CheckAndGetIntPointer( mrb, mrb_p_taskId, 1 );
	/* calling target (MBP120) */
	ret_val = cTECS_getTaskId( p_taskId );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_rotateReadyQueue( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_int	mrb_taskPriority;
	PRI	taskPriority;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "i", &mrb_taskPriority );
	/* convert mrb to C (MBP112) */
	VALCHECK_Int( mrb, mrb_taskPriority );
	taskPriority = (PRI)mrb_taskPriority;
	/* calling target (MBP120) */
	ret_val = cTECS_rotateReadyQueue( taskPriority );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_getTime( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_value	mrb_p_systemTime;
	SYSTIM*	p_systemTime;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "o", &mrb_p_systemTime );
	/* convert mrb to C for pointer types (MBP113) */
	p_systemTime = CheckAndGetULongPointer( mrb, mrb_p_systemTime, 1 );
	/* calling target (MBP120) */
	ret_val = cTECS_getTime( p_systemTime );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_getMicroTime( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_value	mrb_p_systemMicroTime;
	SYSUTM*	p_systemMicroTime;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "o", &mrb_p_systemMicroTime );
	/* convert mrb to C for pointer types (MBP113) */
	p_systemMicroTime = CheckAndGetULongPointer( mrb, mrb_p_systemMicroTime, 1 );
	/* calling target (MBP120) */
	ret_val = cTECS_getMicroTime( p_systemMicroTime );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_lockCpu( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_lockCpu(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_unlockCpu( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_unlockCpu(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_disableDispatch( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_disableDispatch(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_enableDispatch( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_enableDispatch(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_disableTaskException( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_disableTaskException(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_enableTaskException( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_enableTaskException(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_changeInterruptPriorityMask( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_int	mrb_interruptPriority;
	PRI	interruptPriority;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "i", &mrb_interruptPriority );
	/* convert mrb to C (MBP112) */
	VALCHECK_Int( mrb, mrb_interruptPriority );
	interruptPriority = (PRI)mrb_interruptPriority;
	/* calling target (MBP120) */
	ret_val = cTECS_changeInterruptPriorityMask( interruptPriority );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_getInterruptPriorityMask( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_value	mrb_p_interruptPriority;
	PRI*	p_interruptPriority;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "o", &mrb_p_interruptPriority );
	/* convert mrb to C for pointer types (MBP113) */
	p_interruptPriority = CheckAndGetIntPointer( mrb, mrb_p_interruptPriority, 1 );
	/* calling target (MBP120) */
	ret_val = cTECS_getInterruptPriorityMask( p_interruptPriority );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_exitKernel( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_exitKernel(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_senseContext( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	bool_t	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_senseContext(  );
	/* return (MBP130) */
	return ret_val ? mrb_true_value() : mrb_false_value();
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_senseLock( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	bool_t	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_senseLock(  );
	/* return (MBP130) */
	return ret_val ? mrb_true_value() : mrb_false_value();
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_senseDispatch( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	bool_t	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_senseDispatch(  );
	/* return (MBP130) */
	return ret_val ? mrb_true_value() : mrb_false_value();
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_senseDispatchPendingState( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	bool_t	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_senseDispatchPendingState(  );
	/* return (MBP130) */
	return ret_val ? mrb_true_value() : mrb_false_value();
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsKernel_senseKernel( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsKernel *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	bool_t	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_senseKernel(  );
	/* return (MBP130) */
	return ret_val ? mrb_true_value() : mrb_false_value();
}
/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
