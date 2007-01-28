#ifndef PSTADE_OVEN_TAKEN_WHILE_HPP
#define PSTADE_OVEN_TAKEN_WHILE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./take_while_iterator.hpp"


namespace pstade { namespace oven {


namespace taken_while_detail {


    template< class Range, class Predicate >
    struct baby
    {
        typedef
            take_while_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<Predicate>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng, Predicate& pred)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            return result(
                iter_t(boost::begin(rng), boost::end(rng), pred),
                iter_t(boost::end(rng),   boost::end(rng), pred)
            );
        }
    };


} // namespace taken_while_detail


PSTADE_FUNCTION(make_taken_while, (taken_while_detail::baby<_, _>))
PSTADE_PIPABLE(taken_while, (op_make_taken_while))


} } // namespace pstade::oven


#endif
