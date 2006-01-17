#pragma once 

#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
	#pragma warning(push)
	#pragma warning(disable:4663)
#endif


#include "detail/push_macro_max_min.hpp"


#include <iterator>	// for std::distance
#include <limits>		// for std::numeric_limits
#include <boost/iterator/iterator_traits.hpp> // for boost::iterator_difference
#include <boost/mpl/void.hpp>
#include <boost/range/result_iterator.hpp>
#include "../../state/advance.hpp"


#if defined(PSTADE_BISCUIT_CFG_NO_PREPROCESSED_HEADERS)
	#include "../../detail/preprocessing/shortestn.hpp"
#else
	#include "../../detail/preprocessed/shortestn.hpp"
#endif


#include "./detail/pop_macro_max_min.hpp"


#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
	#pragma warning(pop)
#endif
