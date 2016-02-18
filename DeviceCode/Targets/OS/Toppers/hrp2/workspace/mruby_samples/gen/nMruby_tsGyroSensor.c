/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 呼び口関数 #_TCPF_#
 * call port: cTECS signature: sGyroSensor context:task 
 *   int16_t        cTECS_getAngle( );
 *   int16_t        cTECS_getRate( );
 *   ER             cTECS_reset( );
 *   float32_t      cTECS_calibrate( int32_t times );
 *   void           cTECS_initializePort( );
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "nMruby_tsGyroSensor_tecsgen.h"

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
tsGyroSensor_free( mrb_state *mrb, void *p )
{
	if( p )
		(void)mrb_free( mrb, p );
}

/* RData MBP002 */
struct mrb_data_type data_type_tsGyroSensor =
{
	"tsGyroSensor",
	tsGyroSensor_free
};

/* RData MBP003 */
struct tecs_tsGyroSensor {
    CELLCB  *cbp;
};

/* name_to_cbp MBP010 */
const struct name_to_cbp_tsGyroSensor {
    char   *name;    /* Cell Name */
    CELLCB *cbp;
} Name_to_cbp_tsGyroSensor[] = {
	{ "BridgeGyroSensor1", &nMruby_tsGyroSensor_CB_tab[0] },
	{ "BridgeGyroSensor2", &nMruby_tsGyroSensor_CB_tab[1] },
	{ "BridgeGyroSensor3", &nMruby_tsGyroSensor_CB_tab[2] },
	{ "BridgeGyroSensor4", &nMruby_tsGyroSensor_CB_tab[3] },
	{ 0, 0 },
};


/* MBP100 */
mrb_value
MrubyBridge_tsGyroSensor_initialize( mrb_state *mrb, mrb_value self)
{
	mrb_value	name;
	struct tecs_tsGyroSensor *tecs_cb;
	const struct name_to_cbp_tsGyroSensor *ntc;

	/* set DATA_TYPE earlier to avoid SEGV */
	DATA_TYPE( self ) = &data_type_tsGyroSensor;

	mrb_get_args(mrb, "o", &name );
	if( mrb_type( name ) != MRB_TT_STRING ){
		mrb_raise(mrb, E_NAME_ERROR, "cell name not string");
	}
	for( ntc = &Name_to_cbp_tsGyroSensor[0]; ntc->name != NULL; ntc++ ){
		if( strcmp( ntc->name, RSTRING_PTR( name ) ) == 0 )
			break;
	}
	if( ntc->name == 0 ){
		mrb_raise(mrb, E_ARGUMENT_ERROR, "cell not found");
	}
	tecs_cb = (struct tecs_tsGyroSensor *)mrb_malloc(mrb, sizeof(struct tecs_tsGyroSensor) );
	tecs_cb->cbp = ntc->cbp;
	DATA_PTR( self ) = (void *)tecs_cb;

	return self;
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsGyroSensor_getAngle( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsGyroSensor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	int16_t	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_getAngle(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsGyroSensor_getRate( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsGyroSensor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	int16_t	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_getRate(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsGyroSensor_reset( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsGyroSensor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_reset(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsGyroSensor_calibrate( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsGyroSensor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	float32_t	ret_val;
	mrb_int	mrb_times;
	int32_t	times;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "i", &mrb_times );
	/* convert mrb to C (MBP112) */
	VALCHECK_Int32( mrb, mrb_times );
	times = (int32_t)mrb_times;
	/* calling target (MBP120) */
	ret_val = cTECS_calibrate( times );
	/* return (MBP130) */
	return mrb_float_value( mrb, ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsGyroSensor_initializePort( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsGyroSensor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	/* calling target (MBP120) */
	cTECS_initializePort(  );
	/* return (MBP130) */
	return  mrb_nil_value();
}
/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
