#pragma once

// Note:
//   For VC7.1, Set of small if-statement seems faster than one big if-statement.

#include <boost/mpl/void.hpp>

#include "../state/cur_guard.hpp"

#if defined(PSTADE_BISCUIT_CFG_NO_PREPROCESSED_HEADERS)
	#include "../detail/preprocessing/seqn.hpp"
#else
	#include "../detail/preprocessed/seqn.hpp"
#endif
