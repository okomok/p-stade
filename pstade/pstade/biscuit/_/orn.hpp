#pragma once

// Note:
//   For VC7.1, Set of small if-statement seems faster than one big if-statement.

#include <boost/mpl/void.hpp>


#if defined(PSTADE_BISCUIT_CFG_NO_PREPROCESSED_HEADERS)
	#include "../detail/preprocessing/orn.hpp"
#else
	#include "../detail/preprocessed/orn.hpp"
#endif
