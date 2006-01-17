#pragma once

// VC6 can't order two constructor/operators of boost::iterator_range,
// if implicitly generated.

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>


#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
	#define PSTADE_OVEN_WORKAROUND_ITERATOR_RANGE_OVERLOAD_AMBIGUITY(t, it) \
	/**/
#else
	#define PSTADE_OVEN_WORKAROUND_ITERATOR_RANGE_OVERLOAD_AMBIGUITY(t, it) \
		t(const t& other) : \
			boost::iterator_range<it>(other.begin(), other.end()) \
		{ } \
		\
		t& operator=(const t& other) \
		{ \
			boost::iterator_range<it>::operator=(other); \
			return *this; \
		} \
	/**/
#endif
