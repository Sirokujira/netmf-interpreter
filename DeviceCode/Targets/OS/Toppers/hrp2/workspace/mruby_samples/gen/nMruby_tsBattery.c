/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 呼び口関数 #_TCPF_#
 * call port: cTECS signature: sBattery context:task 
 *   int            cTECS_current_mA( );
 *   int            cTECS_voltage_mV( );
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "nMruby_tsBattery_tecsgen.h"

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
tsBattery_free( mrb_state *mrb, void *p )
{
	if( p )
		(void)mrb_free( mrb, p );
}

/* RData MBP002 */
struct mrb_data_type data_type_tsBattery =
{
	"tsBattery",
	tsBattery_free
};

/* RData MBP003 */
struct tecs_tsBattery {
    CELLCB  *cbp;
};

/* name_to_cbp MBP010 */
const struct name_to_cbp_tsBattery {
    char   *name;    /* Cell Name */
    CELLCB *cbp;
} Name_to_cbp_tsBattery[] = {
	{ "BridgeBattery", NULL },
	{ 0, 0 },
};


/* MBP100 */
mrb_value
MrubyBridge_tsBattery_initialize( mrb_state *mrb, mrb_value self)
{
	mrb_value	name;
	struct tecs_tsBattery *tecs_cb;
	const struct name_to_cbp_tsBattery *ntc;

	/* set DATA_TYPE earlier to avoid SEGV */
	DATA_TYPE( self ) = &data_type_tsBattery;

	mrb_get_args(mrb, "o", &name );
	if( mrb_type( name ) != MRB_TT_STRING ){
		mrb_raise(mrb, E_NAME_ERROR, "cell name not string");
	}
	for( ntc = &Name_to_cbp_tsBattery[0]; ntc->name != NULL; ntc++ ){
		if( strcmp( ntc->name, RSTRING_PTR( name ) ) == 0 )
			break;
	}
	if( ntc->name == 0 ){
		mrb_raise(mrb, E_ARGUMENT_ERROR, "cell not found");
	}
	tecs_cb = (struct tecs_tsBattery *)mrb_malloc(mrb, sizeof(struct tecs_tsBattery) );
	tecs_cb->cbp = ntc->cbp;
	DATA_PTR( self ) = (void *)tecs_cb;

	return self;
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsBattery_current_mA( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsBattery *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	int	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_current_mA(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsBattery_voltage_mV( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsBattery *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	int	ret_val;
	/* calling target (MBP120) */
	ret_val = cTECS_voltage_mV(  );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}
/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
