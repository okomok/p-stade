#ifndef PSTADE_OVEN_ARRAY_PROTECT_RANGE_HPP
#define PSTADE_OVEN_ARRAY_PROTECT_RANGE_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Workaround for:
//   Under below Boost 1.34, char array is regarded as null-terminated.


#include <cstddef> // size_t
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp> // true_
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/extent.hpp>
#include <boost/type_traits/is_array.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./sub_range_base_type.hpp"


namespace pstade { namespace oven {


namespace array_protect_range_detail {


	template< class T > inline
	boost::iterator_range< T * >
	aux(T *arr, std::size_t sz)
	{
		return boost::make_iterator_range(arr, arr + sz);
	}


} // namespace array_protect_range_detail


template< class ArrayT >
struct array_protect_range :
	sub_range_base<ArrayT>::type
{
	BOOST_MPL_ASSERT((boost::is_array<ArrayT>));

private:
	typedef typename sub_range_base<ArrayT>::type super_t;

public:
	explicit array_protect_range(ArrayT& arr) :
		super_t(array_protect_range_detail::aux(arr, boost::extent<ArrayT>::value))
	{ }
};


namespace array_protect_range_detail {


	struct baby_generator
	{
		template< class ArrayT >
		struct apply
		{
			// 'const' works around "Forwarding Problem".
			typedef const array_protect_range<ArrayT> type;
		};

		template< class Result, class ArrayT >
		Result call(ArrayT& arr)
		{
			return Result(arr);
		}
	};


} // namespace array_protect_range_detail


PSTADE_EGG_FUNCTION(make_array_protect_range, array_protect_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(array_protected, array_protect_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::array_protect_range, 1)


#endif
