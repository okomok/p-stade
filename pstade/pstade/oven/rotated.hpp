#ifndef PSTADE_OVEN_ROTATED_HPP
#define PSTADE_OVEN_ROTATED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./iter_range.hpp"
#include "./jointed.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace rotated_detail {


    template< class Range >
    struct base
    {
        typedef typename
            iter_range_of<Range>::type
        rng_t;

        typedef typename
            result_of<
                T_make_jointed(rng_t, rng_t)
            >::type
        result_type;

        template< class MiddleFun >
        result_type operator()(Range& rng, MiddleFun fun) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));

            typename range_iterator<Range>::type mid = fun(rng);
            return make_jointed(rng_t(mid, boost::end(rng)), rng_t(boost::begin(rng), mid));
        }
    };


} // namespace rotated_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(rotated, (rotated_detail::base<_>))


} } // namespace pstade::oven


#endif
