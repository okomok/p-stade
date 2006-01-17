#pragma once

#include <boost/range/const_iterator.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/value_type.hpp>

namespace pstade { namespace tomato {


template< class T >
struct single_pass_range
{
	typedef typename boost::range_value<T>::type value_t;
	typedef typename boost::range_iterator<T>::type iter_t;
	typedef typename boost::range_const_iterator<T>::type const_iter_t;

	void constraints()
	{
		//function_requires< boost::SinglePassIteratorConcept<const_iter_t> >();
		const_constraints(*x);
	}

	void const_constraints(T const& x)
	{
		it = boost::begin(x);
		it = boost::end(x);
		b = boost::empty(x);
	}

	T *x;
	bool b;
	const_iter_t it;
};


} } // namespace pstade::tomato
