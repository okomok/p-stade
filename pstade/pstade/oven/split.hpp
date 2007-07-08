#ifndef PSTADE_OVEN_SPLIT_HPP
#define PSTADE_OVEN_SPLIT_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp>
#include <pstade/egg/not.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./filtered.hpp"
#include "./zipped.hpp"


namespace pstade { namespace oven {


namespace split_detail {


    template< class Range, class Predicate >
    struct base
    {
        typedef typename
            result_of<
                op_make_filtered(Range&, Predicate&)
            >::type
        rng1_t;

        typedef typename
            result_of<
                op_make_filtered(Range&, typename result_of<egg::op_not_(Predicate&)>::type)
            >::type
        rng2_t;

        typedef
            boost::tuples::tuple<rng1_t, rng2_t>
        tuple_t;

        typedef typename
            result_of<
                op_make_zipped(tuple_t)
            >::type
        result_type;

        result_type operator()(Range& rng, Predicate& pred) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));

            return make_zipped(
                tuple_t(
                    make_filtered(rng, pred),
                    make_filtered(rng, egg::not_(rng))
                )
            );
        }
    };


} // namespace split_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(split, (split_detail::base<_, _>))


} } // namespace pstade::oven


#endif
