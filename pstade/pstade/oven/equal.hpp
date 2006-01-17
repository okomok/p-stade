#pragma once

#include <algorithm>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace oven {


template< class Range, class InputIter > inline
bool equal(Range& rng, InputIter first)
{
	return std::equal(boost::begin(rng), boost::end(rng), first);
}

template< class Range, class InputIter, class BinaryPred > inline
bool equal(Range& rng, InputIter first, BinaryPred pred)
{
	return std::equal(boost::begin(rng), boost::end(rng), first, pred);
}


#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)

	template< class Range, class InputIter > inline
	bool equal(const Range& rng, InputIter first)
	{
		return std::equal(boost::const_begin(rng), boost::const_end(rng), first);
	}

	template< class Range, class InputIter, class BinaryPred > inline
	bool equal(const Range& rng, InputIter first, BinaryPred pred)
	{
		return std::equal(boost::const_begin(rng), boost::const_end(rng), first, pred);
	}

#endif // !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)


} } // namespace pstade::oven

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>
