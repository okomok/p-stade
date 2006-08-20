#ifndef PSTADE_OVEN_DETAIL_DEBUG_CONTAINS_HPP
#define PSTADE_OVEN_DETAIL_DEBUG_CONTAINS_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp> // traversal_tag's
#include <boost/range/end.hpp>
#include <pstade/unused.hpp>
#include "../algorithm.hpp" // find
#include "../direct_range.hpp"
#include "../range_traversal.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Range, class Iterator >
bool debug_contains_aux(Range& rng, Iterator const& it, boost::forward_traversal_tag)
{
    if (it == boost::end(rng))
        return true;

    direct_range<Range> drng(rng);
    return oven::find(drng, it) != boost::end(drng);
}


template< class Range, class Iterator > inline
bool debug_contains_aux(Range& rng, Iterator const& it, boost::single_pass_traversal_tag)
{
    pstade::unused(rng);
    return 0;
}


template< class Range, class Iterator > inline
bool debug_contains(Range& rng, Iterator const& it)
{
    typedef typename range_traversal<Range>::type trv_t;
    return detail::debug_contains_aux(rng, it, trv_t());
}


} } } // namespace pstade::oven::detail


#endif
