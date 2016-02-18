/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 呼び口関数 #_TCPF_#
 * call port: cTECS signature: sBalancer context:task 
 *   void           cTECS_control( float32_t forward, float32_t turn, float32_t gyro, float32_t gyroOffset, float32_t leftRevolution, float32_t rightRevolution, float32_t battery, int8_t* pwm_l, int8_t* pwm_r );
 *   void           cTECS_init( );
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "nMruby_tsBalancer_tecsgen.h"

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
tsBalancer_free( mrb_state *mrb, void *p )
{
	if( p )
		(void)mrb_free( mrb, p );
}

/* RData MBP002 */
struct mrb_data_type data_type_tsBalancer =
{
	"tsBalancer",
	tsBalancer_free
};

/* RData MBP003 */
struct tecs_tsBalancer {
    CELLCB  *cbp;
};

/* name_to_cbp MBP010 */
const struct name_to_cbp_tsBalancer {
    char   *name;    /* Cell Name */
    CELLCB *cbp;
} Name_to_cbp_tsBalancer[] = {
	{ "BridgeBalancer", NULL },
	{ 0, 0 },
};


/* MBP100 */
mrb_value
MrubyBridge_tsBalancer_initialize( mrb_state *mrb, mrb_value self)
{
	mrb_value	name;
	struct tecs_tsBalancer *tecs_cb;
	const struct name_to_cbp_tsBalancer *ntc;

	/* set DATA_TYPE earlier to avoid SEGV */
	DATA_TYPE( self ) = &data_type_tsBalancer;

	mrb_get_args(mrb, "o", &name );
	if( mrb_type( name ) != MRB_TT_STRING ){
		mrb_raise(mrb, E_NAME_ERROR, "cell name not string");
	}
	for( ntc = &Name_to_cbp_tsBalancer[0]; ntc->name != NULL; ntc++ ){
		if( strcmp( ntc->name, RSTRING_PTR( name ) ) == 0 )
			break;
	}
	if( ntc->name == 0 ){
		mrb_raise(mrb, E_ARGUMENT_ERROR, "cell not found");
	}
	tecs_cb = (struct tecs_tsBalancer *)mrb_malloc(mrb, sizeof(struct tecs_tsBalancer) );
	tecs_cb->cbp = ntc->cbp;
	DATA_PTR( self ) = (void *)tecs_cb;

	return self;
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsBalancer_control( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsBalancer *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	mrb_float	mrb_forward;
	float32_t	forward;
	mrb_float	mrb_turn;
	float32_t	turn;
	mrb_float	mrb_gyro;
	float32_t	gyro;
	mrb_float	mrb_gyroOffset;
	float32_t	gyroOffset;
	mrb_float	mrb_leftRevolution;
	float32_t	leftRevolution;
	mrb_float	mrb_rightRevolution;
	float32_t	rightRevolution;
	mrb_float	mrb_battery;
	float32_t	battery;
	mrb_value	mrb_pwm_l;
	int8_t*	pwm_l;
	mrb_value	mrb_pwm_r;
	int8_t*	pwm_r;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "fffffffoo", &mrb_forward, &mrb_turn, &mrb_gyro, &mrb_gyroOffset, &mrb_leftRevolution, &mrb_rightRevolution, &mrb_battery, &mrb_pwm_l, &mrb_pwm_r );
	/* convert mrb to C (MBP112) */
	forward = (float32_t)mrb_forward;
	turn = (float32_t)mrb_turn;
	gyro = (float32_t)mrb_gyro;
	gyroOffset = (float32_t)mrb_gyroOffset;
	leftRevolution = (float32_t)mrb_leftRevolution;
	rightRevolution = (float32_t)mrb_rightRevolution;
	battery = (float32_t)mrb_battery;
	/* convert mrb to C for pointer types (MBP113) */
	pwm_l = CheckAndGetInt8Pointer( mrb, mrb_pwm_l, 1 );
	pwm_r = CheckAndGetInt8Pointer( mrb, mrb_pwm_r, 1 );
	/* calling target (MBP120) */
	cTECS_control( forward, turn, gyro, gyroOffset, leftRevolution, rightRevolution, battery, pwm_l, pwm_r );
	/* return (MBP130) */
	return  mrb_nil_value();
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsBalancer_init( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsBalancer *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	/* calling target (MBP120) */
	cTECS_init(  );
	/* return (MBP130) */
	return  mrb_nil_value();
}
/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
