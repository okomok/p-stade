#pragma once

#include <boost/config.hpp> // for BOOST_MSVC


#if defined(BOOST_MSVC)

	#define PSTADE_WORKAROUND_WARNING_NO_ASSIGNMENT_OPERATOR(t) \
		t& operator=(const t&); \
	/**/

#else

	#define PSTADE_WORKAROUND_WARNING_NO_ASSIGNMENT_OPERATOR(t) \
	/**/

#endif
