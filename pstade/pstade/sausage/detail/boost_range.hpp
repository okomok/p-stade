#ifndef PSTADE_SAUSAGE_DETAIL_BOOST_RANGE_HPP
#define PSTADE_SAUSAGE_DETAIL_BOOST_RANGE_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_reference
#include <boost/range/result_iterator.hpp>
#include <boost/range/value_type.hpp>


namespace pstade { namespace sausage { namespace detail {


struct boost_range
{
	template< class T, class EnumFtor > static
	EnumFtor call(T& x, EnumFtor fun)
	{
		typedef typename boost::range_result_iterator<T>::type iter_t;
		typedef typename boost::iterator_reference<iter_t>::type ref_t;
		
		BOOST_FOREACH (ref_t val, x) {
			if (!fun(val))
				break;
		}

		return fun;
	}

	typedef boost_range type;
};


template< class T >
struct boost_range_argument
{
	typedef typename boost::range_result_iterator<T>::type iter_t;
	typedef typename boost::iterator_reference<iter_t>::type type;
};


} } } // namespace pstade::sausage::detail


#endif
