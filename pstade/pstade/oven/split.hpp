#ifndef PSTADE_OVEN_SPLIT_HPP
#define PSTADE_OVEN_SPLIT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/prelude.hpp"
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/functional.hpp> // not_
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./filtered.hpp"
#include "./zipped.hpp"


namespace pstade { namespace oven {


namespace split_detail {


    template< class Range, class Predicate >
    struct baby
    {
        typedef typename
            boost::result_of<
                op_make_filtered(Range&, Predicate&)
            >::type
        rng1_t;

        typedef typename
            boost::result_of<
                op_make_filtered(Range&, typename boost::result_of<pstade::op_not(Predicate&)>::type)
            >::type
        rng2_t;

        typedef
            boost::tuples::tuple<rng1_t, rng2_t>
        tuple_t;

        typedef typename
            boost::result_of<
                op_make_zipped(tuple_t)
            >::type
        result_type;

        result_type operator()(Range& rng, Predicate& pred) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));

            return make_zipped(
                tuple_t(
                    make_filtered(rng, pred),
                    make_filtered(rng, pstade::not_(rng))
                )
            );
        }
    };


} // namespace split_detail


PSTADE_FUNCTION(make_split, (split_detail::baby<_, _>))
PSTADE_PIPABLE(split, (op_make_split))


} } // namespace pstade::oven


#endif
