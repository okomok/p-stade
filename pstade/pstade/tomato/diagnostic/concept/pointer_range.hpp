#pragma once

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>
#include "random_access_range.hpp"

namespace pstade { namespace tomato {


template< class T >
struct pointer_range
{
	typedef typename boost::range_value<T>::type value_t;

	void constraints()
	{
		boost::function_requires< random_access_range<T> >();
		const_constraints(*x);
	}
	
	void const_constraints(T const& x)
	{
		it = boost::begin(x);
		it = boost::end(x);
	}

	T *x;
	value_t const *it;
};


} } // namespace pstade::tomato
