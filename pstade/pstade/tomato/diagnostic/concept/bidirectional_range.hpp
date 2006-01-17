#pragma once

#include <boost/concept_check.hpp>
#include <boost/range/const_reverse_iterator.hpp>
#include <boost/range/reverse_iterator.hpp>
#include "forward_range.hpp"

namespace pstade { namespace tomato {


template< class T >
struct bidirectional_range
{
	typedef typename boost::range_reverse_iterator<T>::type rev_iter_t;
	typedef typename boost::range_const_reverse_iterator<T>::type const_rev_iter_t;

	void constraints()
	{
		//boost::function_requires< boost::BidirectionalTraversalIterator<T> >();
		boost::function_requires< forward_range<T> >();
		const_constraints(*x);
	}

	void const_constraints(T const& x)
	{
		it = boost::rbegin(x);
		it = boost::rend(x);
	}

	T *x;
	const_rev_iter_t it;
};


} } // namespace pstade::tomato
