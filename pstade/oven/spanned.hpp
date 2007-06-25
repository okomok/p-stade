#ifndef PSTADE_OVEN_SPANNED_HPP
#define PSTADE_OVEN_SPANNED_HPP
#include "./detail/prefix.hpp"


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
#include "./dropped_while.hpp"
#include "./zipped.hpp"


namespace pstade { namespace oven {


namespace spanned_detail {


    template< class Range, class Predicate >
    struct baby
    {
        typedef typename
            boost::result_of<
                op_make_dropped_while(Range&, Predicate&)
            >::type
        rng_t;

        typedef
            boost::tuples::tuple<rng_t, rng_t>
        tuple_t;

        typedef typename
            boost::result_of<
                op_make_zipped(tuple_t)
            >::type
        result_type;

        result_type operator()(Range& rng, Predicate& pred) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));

            rng_t second = make_dropped_while(rng, pred);
            return make_zipped(
                tuple_t(
                    rng_t(boost::begin(rng), boost::begin(second)),
                    second
                )
            );
        }
    };


} // namespace spanned_detail


PSTADE_FUNCTION(make_spanned, (spanned_detail::baby<_, _>))
PSTADE_PIPABLE(spanned, (op_make_spanned))


} } // namespace pstade::oven


#endif
