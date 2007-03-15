#ifndef PSTADE_OVEN_DETAIL_DEBUG_IN_DISTANCE_HPP
#define PSTADE_OVEN_DETAIL_DEBUG_IN_DISTANCE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp>
#include <pstade/for_debug.hpp>
#include <pstade/unused.hpp>
#include "../distance.hpp"
#include "../range_traversal.hpp"


namespace pstade { namespace oven { namespace detail {


// cannot check it on ForwardRange;
// 'rng' may be too long to diagnose.
template< class Difference, class Range > inline
bool debug_in_distance_aux(Difference d, Range& rng, boost::random_access_traversal_tag)
{
    return 0 <= d && d <= distance(rng);
}

template< class Difference, class Range > inline
bool debug_in_distance_aux(Difference d, Range& rng, boost::single_pass_traversal_tag)
{
    unused(rng);
    return 0 <= d;
}


template< class Difference, class Range > inline
bool debug_in_distance(Difference d, Range const& rng)
{
    for_debug();
    return detail::debug_in_distance_aux(d, rng, typename range_traversal<Range>::type());
}


} } } // namespace pstade::oven::detail


#endif
