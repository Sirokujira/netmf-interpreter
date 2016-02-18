/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 呼び口関数 #_TCPF_#
 * call port: cTECS signature: sMotor context:task 
 *   ER_UINT        cTECS_getType( );
 *   int32_t        cTECS_getCounts( );
 *   int            cTECS_getPower( );
 *   ER             cTECS_resetCounts( );
 *   ER             cTECS_setPower( int power );
 *   ER             cTECS_stop( bool_t brake );
 *   ER             cTECS_rotate( int degrees, uint32_t speed_abs, bool_t blocking );
 *   void           cTECS_initializePort( int32_t type );
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "nMruby_tsMotor_tecsgen.h"

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
tsMotor_free( mrb_state *mrb, void *p )
{
	if( p )
		(void)mrb_free( mrb, p );
}

/* RData MBP002 */
struct mrb_data_type data_type_tsMotor =
{
	"tsMotor",
	tsMotor_free
};

/* RData MBP003 */
struct tecs_tsMotor {
    CELLCB  *cbp;
};

/* name_to_cbp MBP010 */
const struct name_to_cbp_tsMotor {
    char   *name;    /* Cell Name */
    CELLCB *cbp;
} Name_to_cbp_tsMotor[] = {
	{ "BridgeMotorA", &nMruby_tsMotor_CB_tab[0] },
	{ "BridgeMotorB", &nMruby_tsMotor_CB_tab[1] },
	{ "BridgeMotorC", &nMruby_tsMotor_CB_tab[2] },
	{ "BridgeMotorD", &nMruby_tsMotor_CB_tab[3] },
	{ 0, 0 },
};


/* MBP100 */
mrb_value
MrubyBridge_tsMotor_initialize( mrb_state *mrb, mrb_value self)
{
	mrb_value	name;
	struct tecs_tsMotor *tecs_cb;
	const struct name_to_cbp_tsMotor *ntc;

	/* set DATA_TYPE earlier to avoid SEGV */
	DATA_TYPE( self ) = &data_type_tsMotor;

	mrb_get_args(mrb, "o", &name );
	if( mrb_type( name ) != MRB_TT_STRING ){
		mrb_raise(mrb, E_NAME_ERROR, "cell name not string");
	}
	for( ntc = &Name_to_cbp_tsMotor[0]; ntc->name != NULL; ntc++ ){
		if( strcmp( ntc->name, RSTRING_PTR( name ) ) == 0 )
			break;
	}
	if( ntc->name == 0 ){
		mrb_raise(mrb, E_ARGUMENT_ERROR, "cell not found");
	}
	tecs_cb = (struct tecs_tsMotor *)mrb_malloc(mrb, sizeof(struct tecs_tsMotor) );
	tecs_cb->cbp = ntc->cbp;
	DATA_PTR( self ) = (void *)tecs_cb;

	return self;
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsMotor_getType( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsMotor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER_UINT	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_getType(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsMotor_getCounts( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsMotor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	int32_t	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_getCounts(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsMotor_getPower( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsMotor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	int	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_getPower(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsMotor_resetCounts( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsMotor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_resetCounts(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsMotor_setPower( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsMotor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_int	mrb_power;
	int	power;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "i", &mrb_power );
	/* convert mrb to C (MBP112) */
	VALCHECK_Int( mrb, mrb_power );
	power = (int)mrb_power;
	/* calling target (MBP120) */
	ret_val = cTECS_setPower( power );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsMotor_stop( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsMotor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_value	mrb_brake;
	bool_t	brake;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "o", &mrb_brake );
	/* convert mrb to C (MBP112) */
	brake = mrb_test( mrb_brake );
	/* calling target (MBP120) */
	ret_val = cTECS_stop( brake );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsMotor_rotate( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsMotor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_int	mrb_degrees;
	int	degrees;
	mrb_int	mrb_speed_abs;
	uint32_t	speed_abs;
	mrb_value	mrb_blocking;
	bool_t	blocking;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "iio", &mrb_degrees, &mrb_speed_abs, &mrb_blocking );
	/* convert mrb to C (MBP112) */
	VALCHECK_Int( mrb, mrb_degrees );
	degrees = (int)mrb_degrees;
	VALCHECK_UInt32( mrb, mrb_speed_abs );
	speed_abs = (uint32_t)mrb_speed_abs;
	blocking = mrb_test( mrb_blocking );
	/* calling target (MBP120) */
	ret_val = cTECS_rotate( degrees, speed_abs, blocking );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsMotor_initializePort( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsMotor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	mrb_int	mrb_type;
	int32_t	type;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "i", &mrb_type );
	/* convert mrb to C (MBP112) */
	VALCHECK_Int32( mrb, mrb_type );
	type = (int32_t)mrb_type;
	/* calling target (MBP120) */
	cTECS_initializePort( type );
	/* return (MBP130) */
	return  mrb_nil_value();
}
/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
