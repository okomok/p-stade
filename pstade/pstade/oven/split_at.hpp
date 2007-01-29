#ifndef PSTADE_OVEN_SPLIT_AT_HPP
#define PSTADE_OVEN_SPLIT_AT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./dropped.hpp"
#include "./zipped.hpp"


namespace pstade { namespace oven {


namespace split_at_detail {


    template< class Range, class Difference >
    struct baby
    {
        typedef typename
            boost::result_of<
                op_make_dropped(Range&, Difference&)
            >::type
        rng_t;

        typedef
            boost::tuples::tuple<rng_t, rng_t>
        tuple_t;

        typedef typename
            boost::result_of<
                op_make_zipped(tuple_t)
            >::type
        result;

        result call(Range& rng, Difference& d)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            rng_t second = make_dropped(rng, d);
            return make_zipped(
                tuple_t(
                    rng_t(boost::begin(rng), boost::begin(second)),
                    second
                )
            );
        }
    };


} // namespace split_at_detail


PSTADE_FUNCTION(make_split_at, (split_at_detail::baby<_, _>))
PSTADE_PIPABLE(split_at, (op_make_split_at))


} } // namespace pstade::oven


#endif
