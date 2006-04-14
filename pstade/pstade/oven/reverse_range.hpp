#ifndef PSTADE_OVEN_REVERSE_RANGE_HPP
#define PSTADE_OVEN_REVERSE_RANGE_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/reverse_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace reverse_range_detail {


	template< class BidiRange >
	struct super_
	{
		typedef boost::iterator_range<
			boost::reverse_iterator<
				typename boost::range_result_iterator<BidiRange>::type
			>
		> type;
	};


} // namespace reverse_range_detail


template< class BidiRange >
struct reverse_range :
	reverse_range_detail::super_<BidiRange>::type
{
	typedef typename boost::range_result_iterator<BidiRange>::type base_iterator;

private:
	typedef typename reverse_range_detail::super_<BidiRange>::type super_t;

public:
	explicit reverse_range(BidiRange& rng) :
		super_t(boost::end(rng), boost::begin(rng))
	{ }
};


namespace reverse_range_detail {


	struct baby_generator
	{
		template< class BidiRange >
		struct apply
		{
			typedef const reverse_range<BidiRange> type;
		};

		template< class Result, class BidiRange >
		Result call(BidiRange& rng)
		{
			return Result(rng);
		}
	};


} // namespace reverse_range_detail


PSTADE_EGG_FUNCTION(make_reverse_range, reverse_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(reversed, reverse_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::reverse_range, 1)


#endif
