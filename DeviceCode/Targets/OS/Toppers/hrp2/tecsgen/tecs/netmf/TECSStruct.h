/*
 *  mruby => TECS brige
 *  
 *   Copyright (C) 2008-2012 by TOPPERS Project
 *--
 *   上記著作権者は，以下の(1)(4)の条件を満たす場合に限り，本ソフトウェ
 *   ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *   変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *   (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *       権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *       スコード中に含まれていること．
 *   (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *       用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *       者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *       の無保証規定を掲載すること．
 *   (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *       用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *       と．
 *     (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *         作権表示，この利用条件および下記の無保証規定を掲載すること．
 *     (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *         報告すること．
 *   (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *       害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *       また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *       由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *       免責すること．
 *  
 *   本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *   よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *   に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *   アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *   の責任を負わない．
 *  
 *   $Id: TECSStruct.h 2027 2014-01-20 08:36:17Z okuma-top $ 
 */

#ifndef TECSStruct_h__
#define TECSStruct_h__

#define MEMBER_GET_SET_INT( TAG, MEMBER, Type, TYPE )					\
	static netmf_value													\
	Struct_ ## TAG ## _ ## MEMBER ## _aget(netmf_state *netmf, netmf_value self)	\
	{																	\
		struct TAG *st = DATA_PTR( self );								\
		TYPE ## _t	val;												\
																		\
		val = st->MEMBER;												\
		VALCHECK_MRB_ ## Type( netmf, val );								\
		return netmf_fixnum_value( val );									\
	}																	\
																		\
	static netmf_value													\
	Struct_ ## TAG ## _ ## MEMBER ## _aset(netmf_state *netmf, netmf_value self)	\
	{																	\
		struct TAG *st = DATA_PTR( self );								\
		netmf_int	val;													\
																		\
		netmf_get_args(netmf, "i", &val );									\
																		\
		VALCHECK_ ## Type ( netmf, val );									\
		st->MEMBER = val;												\
																		\
		return self;													\
	}

#define MEMBER_GET_SET_FLOAT( TAG, MEMBER )								\
	static netmf_value													\
	Struct_ ## TAG ## _ ## MEMBER ## _aget(netmf_state *netmf, netmf_value self)	\
	{																	\
		struct TAG *st = DATA_PTR( self );								\
																		\
		return netmf_float_value( netmf, st->MEMBER );                      \
	}																	\
																		\
	static netmf_value													\
	Struct_ ## TAG ## _ ## MEMBER ## _aset(netmf_state *netmf, netmf_value self)	\
	{																	\
		struct TAG *st = DATA_PTR( self );								\
		netmf_float	val;												\
																		\
		netmf_get_args(netmf, "f", &val );									\
																		\
		st->MEMBER = val;												\
																		\
		return self;													\
	}

////  define Struct class ////
#define STRUCT_CLASS( TAG )												\
																		\
	static void															\
	Struct ## TAG ## Body_free( netmf_state *netmf, void *p )				\
	{																	\
		(void)netmf_free( netmf, p );										\
	}																	\
																		\
	struct netmf_data_type Struct ## TAG ## Body_netmf_data_type =			\
		{																\
			"TECS::Struct" #TAG,										\
			Struct ## TAG ## Body_free									\
		};																\
																		\
	static netmf_value													\
	Struct_ ## TAG ## _initialize( netmf_state *netmf, netmf_value self)		\
	{																	\
		netmf_int	length;													\
		struct  TAG *structBody;										\
																		\
		DATA_TYPE( self ) = &Struct ## TAG ## Body_netmf_data_type;		\
		DATA_PTR( self ) = netmf_malloc(netmf, sizeof(struct TAG)); 		\
						 												\
		return self;													\
	}

#define  STRUCT_INIT_BEGIN( TAG )										\
	struct RClass *														\
	tecs_init_Struct_## TAG(netmf_state *netmf, struct RClass *TECS)		\
	{																	\
		struct RClass *a;												\
																		\
		a = netmf_define_class_under(netmf, TECS, "Struct" #TAG, netmf->object_class); \
		MRB_SET_INSTANCE_TT(a, MRB_TT_DATA);							\
																		\
		netmf_define_method(netmf, a, "initialize", Struct_ ## TAG ## _initialize,            ARGS_NONE());

#define  STRUCT_INIT_MEMBER( TAG, MEMBER )								\
		netmf_define_method(netmf, a, #MEMBER,      Struct_ ## TAG ## _ ## MEMBER ## _aget,   ARGS_NONE()); \
		netmf_define_method(netmf, a, #MEMBER "=",  Struct_ ## TAG ## _ ## MEMBER ## _aset,   ARGS_REQ(1));


#define  STRUCT_INIT_END( TAG )											\
	}

#define CHECK_STRUCT( tag, value )										\
	do {																\
		if( netmf_type(value) != MRB_TT_DATA								\
			|| DATA_TYPE( value ) == 0									\
			|| strcmp( DATA_TYPE( value )->struct_name, "TECS::Struct" #tag ) ) \
			netmf_raise(netmf, E_TYPE_ERROR, "not Struct or tag mismatch"); \
	}while(0)

#endif /* TECSStruct_h__ */
