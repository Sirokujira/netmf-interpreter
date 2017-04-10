/*
 * TestDebug.h
 *
 *  Created on: 2012/12/02
 *      Author: Kentaro Sekimoto
 */

#ifndef TESTDEBUG_H_
#define TESTDEBUG_H_

#include <stdarg.h>

#ifdef __cplusplus
extern "C" int _dbg_printf( int ch, const char* format, ...);
#else
int _dbg_printf( int ch, const char* format, ...);
#endif

#define CH_COM  1
#define CH_LCD  2
#define CH_BOTH (CH_COM | CH_LCD)

#ifdef TEST_DEBUG
#define TEST_ENTER(ch)               _dbg_printf(ch, "%s ENTER\n", __FUNCTION__)
#define TEST_EXIT(ch)                _dbg_printf(ch, "%s EXIT \n", __FUNCTION__)
#define TEST_TRACE1(ch, a)           _dbg_printf(ch, (const char *)a)
#define TEST_TRACE2(ch, a, b)        _dbg_printf(ch, (const char *)a, b)
#define TEST_TRACE3(ch, a, b, c)     _dbg_printf(ch, (const char *)a, b, c)
#else
#define TEST_ENTER(ch)
#define TEST_EXIT(ch)
#define TEST_TRACE1(ch, a)
#define TEST_TRACE2(ch, a, b)
#define TEST_TRACE3(ch, a, b, c)
#endif

#endif /* TESTDEBUG_H_ */
