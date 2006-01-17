#pragma once

// Inspired by arnavpoch
//   See: http://groups.yahoo.com/group/wtl/message/12745
//   Not available 'On'Create.

#if defined(_WIN32_WCE) && defined(DEBUG)

	#include <windows.h>
	#include <boost/preprocessor/seq/cat.hpp>
	#include <boost/preprocessor/wstringize.hpp>

	#define PSTADE_TOMATO_WCEASSERT_INFO(exp) \
		BOOST_PP_WSTRINGIZE( BOOST_PP_SEQ_CAT( (__FILE__)([)(__LINE__)(])(:)(exp) ) ) \
	/**/

	#define PSTADE_TOMATO_WCEASSERT(exp) \
		if (!(exp)) \
			::MessageBoxW( \
				NULL, \
				PSTADE_TOMATO_WCEASSERT_INFO(exp), \
				L"Assertion Failed", \
				MB_ICONSTOP \
			); \
	/**/

#else

	#define PSTADE_TOMATO_WCEASSERT(exp) \
	/**/

#endif // defined(_WIN32_WCE) && defined(DEBUG)
