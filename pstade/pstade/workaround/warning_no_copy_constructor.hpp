#pragma once

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)

	#define PSTADE_WORKAROUND_WARNING_NO_COPY_CONSTRUCTOR(t) \
		t(const t&); \
	/**/

#else

	#define PSTADE_WORKAROUND_WARNING_NO_COPY_CONSTRUCTOR(t) \
	/**/

#endif
