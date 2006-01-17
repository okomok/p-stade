#pragma once

#include <boost/concept_check.hpp>
#include <boost/range/iterator.hpp>
#include "bidirectional_range.hpp"

namespace pstade { namespace tomato {


template< class T >
struct random_access_range
{
	typedef typename boost::range_iterator<T>::type iter_t;

	void constraints()
	{
		boost::function_requires< boost::RandomAccessIteratorConcept<iter_t> >();
		boost::function_requires< bidirectional_range<T> >();
	}
};


} } // namespace pstade::tomato
