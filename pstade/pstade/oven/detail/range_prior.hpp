#ifndef PSTADE_OVEN_DETAIL_RANGE_PRIOR_HPP
#define PSTADE_OVEN_DETAIL_RANGE_PRIOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <pstade/unused.hpp>
#include "../range_iterator.hpp"
#include "./next_prior.hpp" // prior


namespace pstade { namespace oven { namespace detail {


template< class ForwardIter > inline
ForwardIter range_prior_aux(ForwardIter first, ForwardIter const& last, boost::bidirectional_traversal_tag)
{
    pstade::unused(first);
    return detail::prior(last);
}


template< class ForwardIter >
ForwardIter range_prior_aux(ForwardIter first, ForwardIter const& last, boost::forward_traversal_tag)
{
    ForwardIter prev(first);
    for (; ++first != last; prev = first)
        ;

    return prev;
}


template< class ForwardIter > inline
ForwardIter range_prior(ForwardIter const& first, ForwardIter const& last)
{
    BOOST_ASSERT("range may not be empty." && first != last);

    typedef typename boost::iterator_traversal<ForwardIter>::type trv_t;
    return detail::range_prior_aux(first, last, trv_t());
}


template< class Range > inline
typename range_iterator<Range>::type range_prior(Range& rng)
{
    return detail::range_prior(boost::begin(rng), boost::end(rng));
}


} } } // namespace pstade::oven::detail


#endif
