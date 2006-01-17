#pragma once

#include <boost/foreach.hpp> // for BOOST_FOREACH_NO_RVALUE_DETECTION


#if defined(BOOST_FOREACH_NO_RVALUE_DETECTION)
	#define PSTADE_WORKAROUND_NO_RVALUE_DETECTION
#endif
