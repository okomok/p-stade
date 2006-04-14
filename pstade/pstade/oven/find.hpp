#ifndef PSTADE_OVEN_FIND_HPP
#define PSTADE_OVEN_FIND_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // find, find_if
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/instance.hpp>
#include <pstade/overload.hpp>


namespace pstade { namespace oven {


namespace find_detail {


	struct gift
	{
		template< class Range, class UnaryPredOrValue >
		struct apply :
			boost::range_result_iterator<Range>
		{ };
	};


	struct if_baby : gift
	{
		template< class Result, class Range, class UnaryPred >
		Result call(Range& rng, UnaryPred pred)
		{
			return std::find_if(boost::begin(rng), boost::end(rng), pred);
		}
	};


	struct baby : gift
	{
		template< class Result, class Range, class Value >
		Result call(Range& rng, const Value& val)
		{
			return pstade_oven_find(rng, val, overload());
		}
	};


} // namespace find_detail


PSTADE_EGG_FUNCTION(find_if, find_detail::if_baby)
PSTADE_EGG_FUNCTION(find, find_detail::baby)


} } // namespace pstade::oven


// default
//
template< class Range, class Value > inline
typename boost::range_result_iterator<Range>::type
pstade_oven_find(Range& rng, const Value& val, ...)
{
	return std::find(boost::begin(rng), boost::end(rng), val);
}


#endif
