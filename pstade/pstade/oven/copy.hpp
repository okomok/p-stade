#pragma once

#include <algorithm>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace pstade { namespace oven {


template< class Range, class OutIter > inline
OutIter copy(const Range& rng, OutIter out)
{
	return std::copy(boost::const_begin(rng), boost::const_end(rng), out);
}


} } // namespace pstade::oven
