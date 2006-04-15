#ifndef PSTADE_TOMATO_ZERO_INITIALIZE_HPP
#define PSTADE_TOMATO_ZERO_INITIALIZE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// To be "= { 0 };" or not to be for consistency.


// Note:
//
// Most of structures needs not to be zero-initialized.


#include <string.h> // memset
#include <boost/static_assert.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/oven/range_adaptor.hpp>


namespace pstade { namespace tomato {


namespace zero_initialize_detail {


	struct baby
	{
		template< class AggregateT >
		struct apply :
			boost::add_reference<AggregateT>
		{ };

		template< class Result, class AggregateT >
		Result call(AggregateT& x)
		{
			// BOOST_STATIC_ASSERT(boost::is_pod<AggregateT>::value); only vc8

			::memset(&x, 0, sizeof(AggregateT));
			return x;
		}
	};


} // namespace zero_initialize_detail


PSTADE_EGG_FUNCTION(zero_initialize, zero_initialize_detail::baby)
PSTADE_OVEN_RANGE_ADAPTOR(zero_initialized, zero_initialize_detail::baby)


/*
template< class AggregateT > inline
AggregateT& zero_initialize(AggregateT& x)
{
	::memset(&x, 0, sizeof(AggregateT));
	return x;
}
*/


} } // namespace pstade::tomato


#endif
