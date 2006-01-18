#pragma once

#include <boost/mpl/void.hpp>

#if !defined(PSTADE_KETCHUP_LIMIT_IDSET_SIZE)
	#define PSTADE_KETCHUP_LIMIT_IDSET_SIZE 30
#endif

#if !defined(PSTADE_KETCHUP_CFG_NO_PREPROCESSED_HEADERS)
	#include "../detail/preprocessed/idsetn.hpp"
#else
	#include "../detail/preprocessing/idsetn.hpp"
#endif
