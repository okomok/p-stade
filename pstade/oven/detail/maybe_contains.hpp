#ifndef PSTADE_OVEN_DETAIL_MAYBE_CONTAINS_HPP
#define PSTADE_OVEN_DETAIL_MAYBE_CONTAINS_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Has no any guarantee. usually works, though; for debug only.


#include <algorithm> // find
#include <iterator> // tags
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/for_debug.hpp>
#include <pstade/result_of.hpp>
#include <pstade/unused.hpp>
#include "../outdirected.hpp"
#include "../range_category.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Range, class Iterator >
bool maybe_contains_aux(Range& rng, Iterator it, std::forward_iterator_tag)
{
    if (it == boost::end(rng))
        return true;

    typename result_of<op_make_outdirected(Range&)>::type drng = make_outdirected(rng);
    return boost::end(drng) != std::find(boost::begin(drng), boost::end(drng), it);
}

template< class Range, class Iterator > inline
bool maybe_contains_aux(Range& rng, Iterator it, std::input_iterator_tag)
{
    unused(rng, it);
    return true;
}


template< class Range, class Iterator > inline
bool maybe_contains(Range const& rng, Iterator it)
{
    for_debug();
    return detail::maybe_contains_aux(rng, it, typename range_category<Range>::type());
}


} } } // namespace pstade::oven::detail


#endif
