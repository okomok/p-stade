#pragma once

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>
#include "pointer_range.hpp"

namespace pstade { namespace tomato {


template< class T >
struct tchar_pointer_range
{
	void constraints()
	{
		boost::function_requires< pointer_range<T> >();
		const_constraints(*x);
	}
	
	void const_constraints(T const& x)
	{
		p = boost::begin(x);
		p = boost::end(x);
	}

	T *x;
	TCHAR const *p;
};


} } // namespace pstade::tomato
