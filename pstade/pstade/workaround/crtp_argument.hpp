#pragma once

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/seq/enum.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, < 1400)

	#define PSTADE_WORKAROUND_CRTP_ARGUMENT(t, seq) \
		t \
	/**/

#else

	#define PSTADE_WORKAROUND_CRTP_ARGUMENT(t, seq) \
		t < BOOST_PP_SEQ_ENUM(seq) > \
	/**/

#endif
