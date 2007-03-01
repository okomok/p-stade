#ifndef PSTADE_OVEN_ROTATED_HPP
#define PSTADE_OVEN_ROTATED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./jointed.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace rotated_detail {


    template< class Range, class >
    struct baby
    {
        typedef typename
            iter_range_of<Range>::type
        rng_t;

        typedef typename
            boost::result_of<
                op_make_jointed(rng_t, rng_t)
            >::type
        result_type;

        template< class MiddleFun >
        result_type operator()(Range& rng, MiddleFun& fun) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));

            typename range_iterator<Range>::type mid = fun(rng);
            return make_jointed(rng_t(mid, boost::end(rng)), rng_t(boost::begin(rng), mid));
        }
    };


} // namespace rotated_detail


PSTADE_FUNCTION(make_rotated, (rotated_detail::baby<_, _>))
PSTADE_PIPABLE(rotated, (op_make_rotated))


} } // namespace pstade::oven


#endif
