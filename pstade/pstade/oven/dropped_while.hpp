#ifndef PSTADE_OVEN_DROPPED_WHILE_HPP
#define PSTADE_OVEN_DROPPED_WHILE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Differently from 'taken_while', this adaptor is not lazy.
// I can't imagine the benefit of something like 'drop_while_iterator'.
// With such iterator, an expression:
// 'counting(1, 10^10)|identities(in_forward)|dropped(10^10 - 1)|reversed;'
// won't hang up. But once you call 'copy', it would be inevitable to hang up.


#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/functional.hpp> // not_
#include <pstade/pipable.hpp>
#include "./algorithm.hpp" // find_if
#include "./concepts.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace dropped_while_detail {


    template< class Range, class >
    struct baby
    {
        typedef typename
            iter_range_of<Range>::type const
        result;

        template< class Predicate >
        result call(Range& rng, Predicate& pred)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return result(find_if(rng, not_(pred)), boost::end(rng));
        }
    };


} // namespace dropped_while_detail


PSTADE_FUNCTION(make_dropped_while, (dropped_while_detail::baby<_, _>))
PSTADE_PIPABLE(dropped_while, (op_make_dropped_while))


} } // namespace pstade::oven


#endif
