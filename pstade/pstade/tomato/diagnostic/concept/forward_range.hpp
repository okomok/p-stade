#pragma once

#include <boost/concept_check.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/size.hpp>
#include <boost/range/size_type.hpp>
#include "single_pass_range.hpp"

namespace pstade { namespace tomato {


template< class T >
struct forward_range
{
	typedef typename boost::range_difference<T>::type diff_t;
	typedef typename boost::range_size<T>::type size_t;

	void constraints()
	{
		//boost::function_requires< boost::ForwardTraversalIteratorConcept<T> >();
		boost::function_requires< single_pass_range<T> >();
		s = boost::size(*x);
	}

	T *x;
	size_t s;
};


} } // namespace pstade::tomato
