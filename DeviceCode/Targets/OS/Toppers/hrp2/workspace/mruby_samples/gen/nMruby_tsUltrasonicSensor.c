/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 呼び口関数 #_TCPF_#
 * call port: cTECS signature: sUltrasonicSensor context:task 
 *   int16_t        cTECS_getDistance( );
 *   bool_t         cTECS_listen( );
 *   void           cTECS_initializePort( );
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "nMruby_tsUltrasonicSensor_tecsgen.h"

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
tsUltrasonicSensor_free( mrb_state *mrb, void *p )
{
	if( p )
		(void)mrb_free( mrb, p );
}

/* RData MBP002 */
struct mrb_data_type data_type_tsUltrasonicSensor =
{
	"tsUltrasonicSensor",
	tsUltrasonicSensor_free
};

/* RData MBP003 */
struct tecs_tsUltrasonicSensor {
    CELLCB  *cbp;
};

/* name_to_cbp MBP010 */
const struct name_to_cbp_tsUltrasonicSensor {
    char   *name;    /* Cell Name */
    CELLCB *cbp;
} Name_to_cbp_tsUltrasonicSensor[] = {
	{ "BridgeUltrasonicSensor1", &nMruby_tsUltrasonicSensor_CB_tab[0] },
	{ "BridgeUltrasonicSensor2", &nMruby_tsUltrasonicSensor_CB_tab[1] },
	{ "BridgeUltrasonicSensor3", &nMruby_tsUltrasonicSensor_CB_tab[2] },
	{ "BridgeUltrasonicSensor4", &nMruby_tsUltrasonicSensor_CB_tab[3] },
	{ 0, 0 },
};


/* MBP100 */
mrb_value
MrubyBridge_tsUltrasonicSensor_initialize( mrb_state *mrb, mrb_value self)
{
	mrb_value	name;
	struct tecs_tsUltrasonicSensor *tecs_cb;
	const struct name_to_cbp_tsUltrasonicSensor *ntc;

	/* set DATA_TYPE earlier to avoid SEGV */
	DATA_TYPE( self ) = &data_type_tsUltrasonicSensor;

	mrb_get_args(mrb, "o", &name );
	if( mrb_type( name ) != MRB_TT_STRING ){
		mrb_raise(mrb, E_NAME_ERROR, "cell name not string");
	}
	for( ntc = &Name_to_cbp_tsUltrasonicSensor[0]; ntc->name != NULL; ntc++ ){
		if( strcmp( ntc->name, RSTRING_PTR( name ) ) == 0 )
			break;
	}
	if( ntc->name == 0 ){
		mrb_raise(mrb, E_ARGUMENT_ERROR, "cell not found");
	}
	tecs_cb = (struct tecs_tsUltrasonicSensor *)mrb_malloc(mrb, sizeof(struct tecs_tsUltrasonicSensor) );
	tecs_cb->cbp = ntc->cbp;
	DATA_PTR( self ) = (void *)tecs_cb;

	return self;
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsUltrasonicSensor_getDistance( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsUltrasonicSensor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	int16_t	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_getDistance(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsUltrasonicSensor_listen( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsUltrasonicSensor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	bool_t	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_listen(  );
	/* return (MBP130) */
	return ret_val ? mrb_true_value() : mrb_false_value();
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsUltrasonicSensor_initializePort( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsUltrasonicSensor *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	/* calling target (MBP120) */
	cTECS_initializePort(  );
	/* return (MBP130) */
	return  mrb_nil_value();
}
/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
