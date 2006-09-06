#ifndef PSTADE_OVEN_DETAIL_DEBUG_DISTANCE_HPP
#define PSTADE_OVEN_DETAIL_DEBUG_DISTANCE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp> // traversal_tag's
#include <pstade/for_debug.hpp>
#include <pstade/unused.hpp>
#include "../distance.hpp"
#include "../range_difference.hpp"
#include "../range_traversal.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Range > inline
typename range_difference<Range>::type
debug_distance_aux(Range const& rng, boost::forward_traversal_tag)
{
    return oven::distance(rng);
}


template< class Range > inline
typename range_difference<Range>::type
debug_distance_aux(Range const& rng, boost::single_pass_traversal_tag)
{
    pstade::unused(rng);
    return 0;
}


template< class Range > inline
typename boost::range_difference<Range>::type
debug_distance(Range const& rng)
{
    pstade::for_debug();

    typedef typename range_traversal<Range>::type trv_t;
    return detail::debug_distance_aux(rng, trv_t());
}


} } } // namespace pstade::oven::detail


#endif
