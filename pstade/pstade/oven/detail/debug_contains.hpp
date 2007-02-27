#ifndef PSTADE_OVEN_DETAIL_DEBUG_CONTAINS_HPP
#define PSTADE_OVEN_DETAIL_DEBUG_CONTAINS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



#include <algorithm> // find
#include <iterator> // tags
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/for_debug.hpp>
#include <pstade/unused.hpp>
#include "../directed.hpp"
#include "../range_category.hpp"


namespace pstade { namespace oven { namespace detail {


// Note:
// A Forward Iterator conforms to (24.1.3/1) "is_same(*it1, *it2) => it1 == it2",
// so we can check the containment (am I right?).
// Also note that many Forward Iterators (counting_iterator etc.)
// cannot conform to "is_same(*it1, *it2) <= it1 == it2",
// which is a requirement of Forward Iterator, too.
//

template< class Range, class Iterator >
bool debug_contains_aux(Range& rng, Iterator it, std::forward_iterator_tag)
{
    if (it == boost::end(rng))
        return true;

    typename boost::result_of<op_make_directed(Range&)>::type drng = make_directed(rng);
    return boost::end(drng) != std::find(boost::begin(drng), boost::end(drng), it);
}

template< class Range, class Iterator > inline
bool debug_contains_aux(Range& rng, Iterator it, std::input_iterator_tag)
{
    unused(rng, it);
    return true;
}


template< class Range, class Iterator > inline
bool debug_contains(Range const& rng, Iterator it)
{
    for_debug();
    return (debug_contains_aux)(rng, it, typename range_category<Range>::type());
}


} } } // namespace pstade::oven::detail


#endif
