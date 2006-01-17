#pragma once

#include <algorithm>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/iterator.hpp>
#include <pstade/overload.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace oven {


template< class Range, class Value > inline
typename boost::range_iterator<Range>::type
find(Range& rng, const Value& val)
{
	return pstade_oven_find(rng, val, overload());
}


#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Range, class Value > inline
	typename boost::range_const_iterator<Range>::type
	find(const Range& rng, const Value& val)
	{
		return pstade_oven_find(rng, overload());
	}
#endif 


} } // namespace pstade::oven

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>


// default
template< class Range, class Value > inline
typename boost::range_iterator<Range>::type
pstade_oven_find(Range& rng, const Value& val, ...)
{
	return std::find(boost::begin(rng), boost::end(rng), val);
}
