#ifndef tecs_netmf_h__
#define tecs_netmf_h__

#ifndef TECS

// tecsgen doesn't include actual netmf.h
#include "netmf.h"
#include "netmf/class.h"
#include "netmf/data.h"
#include "netmf/string.h"

#include "TECSPointer.h"
#include "TECSStruct.h"

#else

/*
 * fake tecsgen because tecsgen cannot accept actual netmf.h in case of below.
 *   types:   long long, long long int
 *   special keyword __attribute__(x), __extension__
 */
typedef int netmf_state;
struct  RClass {int dummy;};

typedef int CELLCB;

#endif /* TECS */

#endif /* tecs_netmf_h__ */
