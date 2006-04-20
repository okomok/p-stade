#ifndef PSTADE_OVEN_REPLICATE_RANGE_HPP
#define PSTADE_OVEN_REPLICATE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/remove_rcv.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./repeat_iterator.hpp"
#include "./sub_range_result_type.hpp"


namespace pstade { namespace oven {


namespace repeat_range_detail {


	template< class Range, class CountT >
	struct super_
	{
		typedef boost::iterator_range<
			repeat_iterator<
				typename boost::range_result_iterator<Range>::type,
				CountT
			>
		> type;
	};


} // namespace repeat_range_detail


template< class Range, class CountT = std::size_t >
struct repeat_range :
	repeat_range_detail::super_<Range, CountT>::type
{
private:
	typedef typename repeat_range_detail::super_<Range, CountT>::type super_t;
	typedef typename super_t::iterator iter_t;

public:
	explicit repeat_range(Range& rng, CountT count) :
		super_t(
			iter_t(boost::begin(rng), boost::end(rng), count),
			iter_t(boost::begin(rng), boost::end(rng), 0)
		)
	{ }

	typename sub_range_result<Range>::type source() const
	{
		return boost::make_iterator_range(
			this->begin().source_begin(),
			this->begin().source_end()
		);
	}
};


namespace repeat_range_detail {


	struct baby_generator
	{
		template< class Range, class CountT >
		struct apply
		{
			typedef typename remove_rcv<CountT>::type count_t;
			typedef const repeat_range<Range, count_t> type;
		};

		template< class Result, class Range, class CountT >
		Result call(Range& rng, CountT count)
		{
			return Result(rng, count);
		}
	};


} // namespace repeat_range_detail


PSTADE_EGG_FUNCTION(make_repeat_range, repeat_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(repeated, repeat_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::repeat_range, 2)


#endif
