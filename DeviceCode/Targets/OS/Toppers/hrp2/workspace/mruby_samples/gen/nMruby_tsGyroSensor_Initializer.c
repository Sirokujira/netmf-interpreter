/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "nMruby_tsGyroSensor_Initializer_tecsgen.h"

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
//  Prototype MBP400
mrb_value  MrubyBridge_tsGyroSensor_initialize( mrb_state *mrb, mrb_value self);
mrb_value  MrubyBridge_tsGyroSensor_getAngle( mrb_state *mrb, mrb_value self );
mrb_value  MrubyBridge_tsGyroSensor_getRate( mrb_state *mrb, mrb_value self );
mrb_value  MrubyBridge_tsGyroSensor_reset( mrb_state *mrb, mrb_value self );
mrb_value  MrubyBridge_tsGyroSensor_calibrate( mrb_state *mrb, mrb_value self );
mrb_value  MrubyBridge_tsGyroSensor_initializePort( mrb_state *mrb, mrb_value self );
/* 受け口関数 #_TEPF_# */
/* #[<ENTRY_PORT>]# eInitialize
 * entry port: eInitialize
 * signature:  nMruby_sInitializeTECSBridge
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eInitialize_initializeBridge
 * name:         eInitialize_initializeBridge
 * global_name:  nMruby_tsGyroSensor_Initializer_eInitialize_initializeBridge
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eInitialize_initializeBridge(CELLIDX idx, mrb_state* mrb, struct RClass * TECS)
{
    CELLCB *p_cellcb = GET_CELLCB( idx );  /* no error check */     /* MBP700 */
    struct RClass	*rc;

    rc = mrb_define_class_under( mrb, TECS, "TsGyroSensor", mrb->object_class );
    mrb_define_method( mrb, rc, "initialize", MrubyBridge_tsGyroSensor_initialize, ARGS_REQ(1) );
    MRB_SET_INSTANCE_TT(rc, MRB_TT_DATA);
	mrb_define_method( mrb, rc, "getAngle", MrubyBridge_tsGyroSensor_getAngle, ARGS_NONE() );
	mrb_define_method( mrb, rc, "getRate", MrubyBridge_tsGyroSensor_getRate, ARGS_NONE() );
	mrb_define_method( mrb, rc, "reset", MrubyBridge_tsGyroSensor_reset, ARGS_NONE() );
	mrb_define_method( mrb, rc, "calibrate", MrubyBridge_tsGyroSensor_calibrate, ARGS_REQ( 1 ) );
	mrb_define_method( mrb, rc, "initializePort", MrubyBridge_tsGyroSensor_initializePort, ARGS_NONE() );
}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
