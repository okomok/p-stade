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
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./dropped_while.hpp"
#include "./zipped.hpp"


namespace pstade { namespace oven {


namespace spanned_detail {


    template< class Range, class Predicate >
    struct base
    {
        typedef typename
            result_of<
                T_make_dropped_while(Range&, Predicate&)
            >::type
        rng_t;

        typedef
            boost::tuples::tuple<rng_t, rng_t>
        tuple_t;

        typedef typename
            result_of<
                T_make_zipped(tuple_t)
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


PSTADE_OVEN_BASE_TO_ADAPTOR(spanned, (spanned_detail::base<_, _>))


} } // namespace pstade::oven


#endif
