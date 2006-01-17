#pragma once 

#include "detail/push_macro_max_min.hpp"


#include <iterator> // for std::distance
#include <boost/iterator/iterator_traits.hpp> // for boost::iterator_difference
#include <boost/mpl/void.hpp>
#include <boost/range/result_iterator.hpp>
#include "../../state/advance.hpp"


#if defined(PSTADE_BISCUIT_CFG_NO_PREPROCESSED_HEADERS)
	#include "../../detail/preprocessing/longestn.hpp"
#else
	#include "../../detail/preprocessed/longestn.hpp"
#endif


#include "./detail/pop_macro_max_min.hpp"
