// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		0x0400
//#define _WIN32_WINNT	0x0400
#define _WIN32_IE	0x0501
#define _RICHEDIT_VER	0x0100

#include <pstade/vodka/begin.hpp>

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _WTL_NO_AUTOMATIC_NAMESPACE

#include <atlbase.h>
#include <atlapp.h>

extern WTL::CAppModule _Module;

#include <atlwin.h>
#include <boost/microsoft/wtl/app.hpp>
