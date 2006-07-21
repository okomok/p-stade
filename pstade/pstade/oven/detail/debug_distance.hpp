#ifndef PSTADE_OVEN_DETAIL_DEBUG_DISTANCE_HPP
#define PSTADE_OVEN_DETAIL_DEBUG_DISTANCE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp> // traversal_tag's
#include <boost/range/difference_type.hpp>
#include <pstade/unused.hpp>
#include "../distance.hpp"
#include "../range_traversal_type.hpp"


namespace pstade { namespace oven { namespace detail {


namespace debug_distance_detail {


    template< class Range > inline
    typename boost::range_difference<Range>::type
    aux(Range const& rng, boost::forward_traversal_tag)
    {
        return oven::distance(rng);
    }


    template< class Range > inline
    typename boost::range_difference<Range>::type
    aux(Range const& rng, boost::single_pass_traversal_tag)
    {
        pstade::unused(rng);
        return 0;
    }


} // namespace debug_distance_detail


template< class Range > inline
typename boost::range_difference<Range>::type
debug_distance(Range const& rng)
{
    typedef typename range_traversal<Range>::type trv_t;
    return debug_distance_detail::aux(rng, trv_t());
}


} } } // namespace pstade::oven::detail


#endif
