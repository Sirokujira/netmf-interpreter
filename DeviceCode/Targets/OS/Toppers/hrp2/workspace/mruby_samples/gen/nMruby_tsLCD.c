/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 呼び口関数 #_TCPF_#
 * call port: cTECS signature: sLCD context:task 
 *   ER             cTECS_setFont( lcdfont_t font );
 *   ER             cTECS_getFontSize( lcdfont_t font, int32_t* p_width, int32_t* p_height );
 *   ER             cTECS_drawString( const char* str, int32_t x, int32_t y );
 *   ER             cTECS_fillRect( int32_t x, int32_t y, int32_t w, int32_t h, lcdcolor_t color );
 *   ER             cTECS_drawLine( int32_t x0, int32_t y0, int32_t x1, int32_t y1 );
 *   void           cTECS_print( const char* str );
 *   void           cTECS_puts( const char* str );
 *   void           cTECS_clear( );
 *   void           cTECS_showMessageBox( const char* title, const char* msg );
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "nMruby_tsLCD_tecsgen.h"

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
tsLCD_free( mrb_state *mrb, void *p )
{
	if( p )
		(void)mrb_free( mrb, p );
}

/* RData MBP002 */
struct mrb_data_type data_type_tsLCD =
{
	"tsLCD",
	tsLCD_free
};

/* RData MBP003 */
struct tecs_tsLCD {
    CELLCB  *cbp;
};

/* name_to_cbp MBP010 */
const struct name_to_cbp_tsLCD {
    char   *name;    /* Cell Name */
    CELLCB *cbp;
} Name_to_cbp_tsLCD[] = {
	{ "BridgeLCD", NULL },
	{ 0, 0 },
};


/* MBP100 */
mrb_value
MrubyBridge_tsLCD_initialize( mrb_state *mrb, mrb_value self)
{
	mrb_value	name;
	struct tecs_tsLCD *tecs_cb;
	const struct name_to_cbp_tsLCD *ntc;

	/* set DATA_TYPE earlier to avoid SEGV */
	DATA_TYPE( self ) = &data_type_tsLCD;

	mrb_get_args(mrb, "o", &name );
	if( mrb_type( name ) != MRB_TT_STRING ){
		mrb_raise(mrb, E_NAME_ERROR, "cell name not string");
	}
	for( ntc = &Name_to_cbp_tsLCD[0]; ntc->name != NULL; ntc++ ){
		if( strcmp( ntc->name, RSTRING_PTR( name ) ) == 0 )
			break;
	}
	if( ntc->name == 0 ){
		mrb_raise(mrb, E_ARGUMENT_ERROR, "cell not found");
	}
	tecs_cb = (struct tecs_tsLCD *)mrb_malloc(mrb, sizeof(struct tecs_tsLCD) );
	tecs_cb->cbp = ntc->cbp;
	DATA_PTR( self ) = (void *)tecs_cb;

	return self;
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsLCD_setFont( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsLCD *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_int	mrb_font;
	lcdfont_t	font;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "i", &mrb_font );
	/* convert mrb to C (MBP112) */
	VALCHECK_Long( mrb, mrb_font );
	font = (lcdfont_t)mrb_font;
	/* calling target (MBP120) */
	ret_val = cTECS_setFont( font );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsLCD_getFontSize( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsLCD *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_int	mrb_font;
	lcdfont_t	font;
	mrb_value	mrb_p_width;
	int32_t*	p_width;
	mrb_value	mrb_p_height;
	int32_t*	p_height;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "ioo", &mrb_font, &mrb_p_width, &mrb_p_height );
	/* convert mrb to C (MBP112) */
	VALCHECK_Long( mrb, mrb_font );
	font = (lcdfont_t)mrb_font;
	/* convert mrb to C for pointer types (MBP113) */
	p_width = CheckAndGetInt32Pointer( mrb, mrb_p_width, 1 );
	p_height = CheckAndGetInt32Pointer( mrb, mrb_p_height, 1 );
	/* calling target (MBP120) */
	ret_val = cTECS_getFontSize( font, p_width, p_height );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsLCD_drawString( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsLCD *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_value	mrb_str;
	const char*	str;
	mrb_int	mrb_x;
	int32_t	x;
	mrb_int	mrb_y;
	int32_t	y;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "oii", &mrb_str, &mrb_x, &mrb_y );
	/* convert mrb to C (MBP112) */
	VALCHECK_Int32( mrb, mrb_x );
	x = (int32_t)mrb_x;
	VALCHECK_Int32( mrb, mrb_y );
	y = (int32_t)mrb_y;
	/* convert mrb to C for pointer types (MBP113) */
	str = CheckAndGetCharPointer( mrb, mrb_str, 1 );
	/* calling target (MBP120) */
	ret_val = cTECS_drawString( str, x, y );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsLCD_fillRect( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsLCD *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_int	mrb_x;
	int32_t	x;
	mrb_int	mrb_y;
	int32_t	y;
	mrb_int	mrb_w;
	int32_t	w;
	mrb_int	mrb_h;
	int32_t	h;
	mrb_int	mrb_color;
	lcdcolor_t	color;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "iiiii", &mrb_x, &mrb_y, &mrb_w, &mrb_h, &mrb_color );
	/* convert mrb to C (MBP112) */
	VALCHECK_Int32( mrb, mrb_x );
	x = (int32_t)mrb_x;
	VALCHECK_Int32( mrb, mrb_y );
	y = (int32_t)mrb_y;
	VALCHECK_Int32( mrb, mrb_w );
	w = (int32_t)mrb_w;
	VALCHECK_Int32( mrb, mrb_h );
	h = (int32_t)mrb_h;
	VALCHECK_Long( mrb, mrb_color );
	color = (lcdcolor_t)mrb_color;
	/* calling target (MBP120) */
	ret_val = cTECS_fillRect( x, y, w, h, color );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsLCD_drawLine( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsLCD *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	ER	ret_val;
	mrb_int	mrb_x0;
	int32_t	x0;
	mrb_int	mrb_y0;
	int32_t	y0;
	mrb_int	mrb_x1;
	int32_t	x1;
	mrb_int	mrb_y1;
	int32_t	y1;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "iiii", &mrb_x0, &mrb_y0, &mrb_x1, &mrb_y1 );
	/* convert mrb to C (MBP112) */
	VALCHECK_Int32( mrb, mrb_x0 );
	x0 = (int32_t)mrb_x0;
	VALCHECK_Int32( mrb, mrb_y0 );
	y0 = (int32_t)mrb_y0;
	VALCHECK_Int32( mrb, mrb_x1 );
	x1 = (int32_t)mrb_x1;
	VALCHECK_Int32( mrb, mrb_y1 );
	y1 = (int32_t)mrb_y1;
	/* calling target (MBP120) */
	ret_val = cTECS_drawLine( x0, y0, x1, y1 );
	/* return (MBP130) */
	return mrb_fixnum_value( ret_val );
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsLCD_print( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsLCD *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	mrb_value	mrb_str;
	const char*	str;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "o", &mrb_str );
	/* convert mrb to C for pointer types (MBP113) */
	str = CheckAndGetCharPointer( mrb, mrb_str, 1 );
	/* calling target (MBP120) */
	cTECS_print( str );
	/* return (MBP130) */
	return  mrb_nil_value();
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsLCD_puts( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsLCD *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	mrb_value	mrb_str;
	const char*	str;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "o", &mrb_str );
	/* convert mrb to C for pointer types (MBP113) */
	str = CheckAndGetCharPointer( mrb, mrb_str, 1 );
	/* calling target (MBP120) */
	cTECS_puts( str );
	/* return (MBP130) */
	return  mrb_nil_value();
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsLCD_clear( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsLCD *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	/* calling target (MBP120) */
	cTECS_clear(  );
	/* return (MBP130) */
	return  mrb_nil_value();
}

/* bridge function (MBP101) */
mrb_value
MrubyBridge_tsLCD_showMessageBox( mrb_state *mrb, mrb_value self )
{
	/* cellcbp (MBP105) */
	CELLCB	*p_cellcb = ((struct tecs_tsLCD *)DATA_PTR(self))->cbp;
	/* variables for return & parameter (MBP110) */
	mrb_value	mrb_title;
	const char*	title;
	mrb_value	mrb_msg;
	const char*	msg;
	/* retrieve arguments (MBP111) */
	mrb_get_args(mrb, "oo", &mrb_title, &mrb_msg );
	/* convert mrb to C for pointer types (MBP113) */
	title = CheckAndGetCharPointer( mrb, mrb_title, 1 );
	msg = CheckAndGetCharPointer( mrb, mrb_msg, 1 );
	/* calling target (MBP120) */
	cTECS_showMessageBox( title, msg );
	/* return (MBP130) */
	return  mrb_nil_value();
}
/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
