// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

// 下で指定された定義の前に対象プラットフォームを指定しなければならない場合、以下の定義を変更してください。
// 異なるプラットフォームに対応する値に関する最新情報については、MSDN を参照してください。
#ifndef WINVER				// Windows XP 以降のバージョンに固有の機能の使用を許可します。
#define WINVER 0x0501		// これを Windows の他のバージョン向けに適切な値に変更してください。
#endif

#ifndef _WIN32_WINNT		// Windows XP 以降のバージョンに固有の機能の使用を許可します。                   
#define _WIN32_WINNT 0x0501	// これを Windows の他のバージョン向けに適切な値に変更してください。
#endif

#ifndef _WIN32_WINDOWS		// Windows 98 以降のバージョンに固有の機能の使用を許可します。
#define _WIN32_WINDOWS 0x0410 // これを Windows Me またはそれ以降のバージョン向けに適切な値に変更してください。
#endif

#ifndef _WIN32_IE			// IE 6.0 以降のバージョンに固有の機能の使用を許可します。
#define _WIN32_IE 0x0600	// これを IE. の他のバージョン向けに適切な値に変更してください。
#endif

#define WIN32_LEAN_AND_MEAN		// Windows ヘッダーから使用されていない部分を除外します。

#include "DebugHeap.h"
#include <new.h>
// Windows ヘッダー ファイル:
// #include <windows.h>
#define SIZE wSIZE
#include <windows.h>
#undef SIZE
#include <tchar.h>

#include <vector>
#include <list>
#include <map>
#include <string>
using namespace std;
typedef basic_string<char> CStringA;
typedef basic_string<wchar_t> CStringW;
typedef basic_string<TCHAR> CString;
#include <fstream>

#define TOPPERS_size	tagSIZE

#ifdef __cplusplus
extern "C" {
#include "kernel_impl.h"
#include "task.h"
}
#else
#include "kernel_impl.h"
#include "task.h"
#endif
