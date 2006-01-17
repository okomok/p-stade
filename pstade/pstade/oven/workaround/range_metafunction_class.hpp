#pragma once

#include <boost/config.hpp>


// Workaround: C4099 warning
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
	#define PSTADE_OVEN_WORKAROUND_RANGE_METAFUNCTION_CLASS struct
#else
	#define PSTADE_OVEN_WORKAROUND_RANGE_METAFUNCTION_CLASS class
#endif
