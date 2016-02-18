#ifndef tecs_mruby_h__
#define tecs_mruby_h__

#ifndef TECS

// tecsgen doesn't include actual mruby.h
#include "mruby.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/string.h"

#include "TECSPointer.h"
#include "TECSStruct.h"

#else

/*
 * fake tecsgen because tecsgen cannot accept actual mruby.h in case of below.
 *   types:   long long, long long int
 *   special keyword __attribute__(x), __extension__
 */
typedef int mrb_state;
struct  RClass {int dummy;};

typedef int CELLCB;

#endif /* TECS */

#endif /* tecs_mruby_h__ */
