#ifndef PSTADE_OVEN_DETAIL_ADVANCE_BEGIN_HPP
#define PSTADE_OVEN_DETAIL_ADVANCE_BEGIN_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // advance
#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/unused.hpp>
#include "../distance.hpp"
#include "../range_traversal.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Range, class Difference > inline
void check_range(Range& rng, Difference d, boost::single_pass_traversal_tag)
{
    BOOST_ASSERT(0 <= d);
    pstade::unused(rng, d);
}


template< class Range, class Difference > inline
void check_range(Range& rng, Difference d, boost::forward_traversal_tag)
{
    BOOST_ASSERT(0 <= d && d <= oven::distance(rng));
    pstade::unused(rng, d);
}


template< class Range, class Difference >
typename boost::range_result_iterator<Range>::type
advance_begin(Range& rng, Difference d)
{
    typedef typename boost::range_result_iterator<Range>::type iter_t;
    typedef typename range_traversal<Range>::type trv_t;
    
    detail::check_range(rng, d, trv_t());
    
    iter_t it = boost::begin(rng);
    std::advance(it, d);
    return it;
}


} } } // namespace pstade::oven::detail


#endif
