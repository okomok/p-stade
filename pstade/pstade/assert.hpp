#pragma once


#if defined(_WIN32_WCE)

	#include <pstade/tomato/diagnostic/wceassert.hpp>
	#define PSTADE_ASSERT PSTADE_TOMATO_WCEASSERT

#elif defined(ATLASSERT)

	#define PSTADE_ASSERT ATLASSERT

#elif defined(ASSERT)

	#define PSTADE_ASSERT ASSERT

#else

	#include <cassert>
	#define PSTADE_ASSERT assert

#endif
