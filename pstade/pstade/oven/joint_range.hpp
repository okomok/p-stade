#ifndef PSTADE_OVEN_JOINT_RANGE_HPP
#define PSTADE_OVEN_JOINT_RANGE_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/egg/function.hpp>
#include "./joint_iterator.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace joint_range_detail {


	template< class Range1, class Range2 >
	struct super_
	{
		typedef boost::iterator_range<
			joint_iterator<
				typename boost::range_result_iterator<Range1>::type,
				typename boost::range_result_iterator<Range2>::type
			>
		> type;
	};


} // namespace joint_range_detail


template< class Range1, class Range2 >
struct joint_range :
	joint_range_detail::super_<Range1, Range2>::type
{
private:
	typedef typename joint_range_detail::super_<Range1, Range2>::type super_t;
	typedef typename super_t::iterator iter_t;

public:
	template< class Range1_, class Range2_ >
	explicit joint_range(Range1_& rng1, Range2_& rng2) :
		super_t(
			oven::make_joint_first_iterator(boost::begin(rng1), boost::end(rng1), boost::begin(rng2)),
			oven::make_joint_second_iterator(boost::end(rng1), boost::begin(rng2), boost::end(rng2))
		)
	{ }
};


namespace joint_range_detail {


	struct baby_generator
	{
		template< class Range1, class Range2 >
		struct apply
		{
			typedef const joint_range<Range1, Range2> type;
		};

		template< class Result, class Range1, class Range2 >
		Result call(Range1& rng1, Range2& rng2)
		{
			return Result(rng1, rng2);
		}
	};


} // namespace joint_range_detail


PSTADE_EGG_FUNCTION(make_joint_range, joint_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(jointed, joint_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::joint_range, 2)


#endif
