#ifndef PSTADE_OVEN_POINTER_RANGE_HPP
#define PSTADE_OVEN_POINTER_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// make Pointer Range from std::vector.


#include <boost/mpl/eval_if.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/size.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/is_const.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/nullptr.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace pointer_range_detail {


	template< class ContiguousRange >
	struct pointer :
		boost::mpl::eval_if< boost::is_const<ContiguousRange>,
			boost::add_pointer<
				typename boost::add_const<
					typename boost::range_value<ContiguousRange>::type
				>::type
			>,
			boost::add_pointer<
				typename boost::range_value<ContiguousRange>::type
			>
		>
	{ };


} // namespace pointer_range_detail


template< class ContiguousRange >
struct pointer_range :
	boost::iterator_range<
		typename pointer_range_detail::pointer<ContiguousRange>::type
	>
{
	typedef boost::iterator_range<
		typename pointer_range_detail::pointer<ContiguousRange>::type
	> super_t;

	explicit pointer_range(ContiguousRange& vec) :
		super_t(
			boost::empty(vec) ? PSTADE_NULLPTR : &*boost::begin(vec), 
			boost::empty(vec) ? PSTADE_NULLPTR : &*boost::begin(vec) + boost::size(vec)
		)
	{ }
};


namespace pointer_range_detail {


	struct baby_generator
	{
		template< class ContiguousRange >
		struct apply
		{
			typedef const pointer_range<ContiguousRange> type;
		};

		template< class Result, class ContiguousRange >
		Result call(ContiguousRange& rng)
		{
			return Result(rng);
		}
	};


} // namespace pointer_range_detail



PSTADE_EGG_FUNCTION(make_pointer_range, pointer_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(pointed, pointer_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::pointer_range, 1)


#endif
