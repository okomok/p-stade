#ifndef PSTADE_OVEN_DROPPED_WHILE_HPP
#define PSTADE_OVEN_DROPPED_WHILE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// Should this be implemented by 'head_iterator' or something,
// which makes this really lazy?


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./drop_while_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace dropped_while_detail {


    template< class Range, class Predicate >
    struct baby
    {
        typedef
            drop_while_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<Predicate>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        template< class Predicate >
        result call(Range& rng, Predicate& pred)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            return result(
                iter_t(boost::begin(rng), boost::end(rng), pred),
                iter_t(boost::end(rng),   boost::end(rng), pred)
            );
        }
    };


} // namespace dropped_while_detail


PSTADE_FUNCTION(make_dropped_while, (dropped_while_detail::baby<_, _>))
PSTADE_PIPABLE(dropped_while, (op_make_dropped_while))


} } // namespace pstade::oven


#endif
