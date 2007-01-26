#ifndef PSTADE_OVEN_DETAIL_DEBUG_IS_SORTED_HPP
#define PSTADE_OVEN_DETAIL_DEBUG_IS_SORTED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/for_debug.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace oven { namespace detail {


template< class ForwardIter, class Compare >
bool iter_is_sorted(ForwardIter first, ForwardIter last, Compare comp)
{
    // See:
    // <boost-sandbox/boost/sequence_algo/algorithm.hpp>

    if (first == last)
        return true;

    for (ForwardIter old = first; ++first != last; old = first) {
        if (comp(*first, *old))
            return false;
    }

    return true;
}


template< class ForwardIter, class Compare > inline
bool debug_is_sorted_aux(ForwardIter first, ForwardIter last, Compare comp,
    boost::forward_traversal_tag)
{
    return detail::iter_is_sorted(first, last, comp);
}


template< class ForwardIter, class Compare > inline
bool debug_is_sorted_aux(ForwardIter first, ForwardIter last, Compare comp,
    boost::single_pass_traversal_tag)
{
    unused(first, last, comp);
    return true;
}


template< class ForwardIter, class Compare > inline
bool debug_is_sorted(ForwardIter first, ForwardIter last, Compare comp)
{
    for_debug();

    typedef typename boost::iterator_traversal<ForwardIter>::type trv_t;
    return detail::debug_is_sorted_aux(first, last, comp, trv_t());
}


} } } // namespace pstade::oven::detail


#endif
