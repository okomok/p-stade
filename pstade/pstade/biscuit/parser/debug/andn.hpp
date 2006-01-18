#pragma once

// Note:
//   For VC7.1, Set of small if-statement seems faster than one big if-statement.

#include <boost/mpl/void.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include "../state/cur_guard.hpp"
#include "../state/match.hpp"


#if defined(PSTADE_BISCUIT_CFG_NO_PREPROCESSED_HEADERS)
	#include "../detail/preprocessing/andn.hpp"
#else
	#include "../detail/preprocessed/andn.hpp"
#endif
