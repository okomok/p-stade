#ifndef PSTADE_OVEN_TRANSFORM_RANGE_HPP
#define PSTADE_OVEN_TRANSFORM_RANGE_HPP


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


#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


template<
	class UnaryFun,
	class Range,
	class Reference = boost::use_default,
	class Value = boost::use_default
>
struct transform_range :
	boost::iterator_range<
		boost::transform_iterator<
			UnaryFun,
			typename boost::range_result_iterator<Range>::type,
			Reference,
			Value
		>
	>
{
	typedef typename boost::range_result_iterator<Range>::type base_iterator;

private:
	typedef boost::transform_iterator<UnaryFun, base_iterator, Reference, Value> iter_t;
	typedef boost::iterator_range<iter_t> super_t;

public:
	explicit transform_range(Range& rng, UnaryFun fun) :
		super_t(
			iter_t(boost::begin(rng), fun), iter_t(boost::end(rng), fun)
		)
	{ }
};


namespace transform_range_detail {


	struct baby_generator
	{
		template< class Range, class UnaryFun >
		struct apply
		{
			typedef typename boost::remove_cv<UnaryFun>::type fun_t;
			typedef const transform_range<fun_t, Range> type;
		};

		template< class Result, class Range, class UnaryFun >
		Result call(Range& rng, UnaryFun& fun)
		{
			return Result(rng, fun);
		}
	};


} // namespace transform_range_detail


PSTADE_EGG_FUNCTION(make_transform_range, transform_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(transformed, transform_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::transform_range, 4)


#endif
