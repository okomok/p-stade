#ifndef PSTADE_OVEN_ADJACENT_FILTERERD_HPP
#define PSTADE_OVEN_ADJACENT_FILTERERD_HPP


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
#include "./adjacent_filter_iterator.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace adjacent_filtered_detail {


    template< class Range, class BinaryPred >
    struct baby
    {
        typedef
            adjacent_filter_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<BinaryPred>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng, BinaryPred& pred)
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));

            return result(
               iter_t(boost::begin(rng), pred, boost::begin(rng), boost::end(rng)),
               iter_t(boost::end(rng),   pred, boost::begin(rng), boost::end(rng))
            );
        }
    };


} // namespace adjacent_filtered_detail


PSTADE_FUNCTION(make_adjacent_filtered, (adjacent_filtered_detail::baby<_, _>))
PSTADE_PIPABLE(adjacent_filtered, (op_make_adjacent_filtered))


} } // namespace pstade::oven


#endif
