#ifndef PSTADE_OVEN_DROPPED_WHILE_HPP
#define PSTADE_OVEN_DROPPED_WHILE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// Should this be implemented by 'head_iterator' or something,
// which makes this really lazy?


#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/functional.hpp> // not_
#include <pstade/pipable.hpp>
#include "./algorithm.hpp" // find_if
#include "./concepts.hpp"
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


namespace dropped_while_detail {


    template< class Range, class >
    struct baby
    {
        typedef typename
            sub_range_result<Range>::type
        result;

        template< class Predicate >
        result call(Range& rng, Predicate& pred)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            // PSTADE_CONCEPT_ASSERT((Readable<Range>));

            return result(oven::find_if(rng, not_(pred)), boost::end(rng));
        }
    };


} // namespace dropped_while_detail


PSTADE_FUNCTION(make_dropped_while, (dropped_while_detail::baby<_, _>))
PSTADE_PIPABLE(dropped_while, (op_make_dropped_while))


} } // namespace pstade::oven


#endif
