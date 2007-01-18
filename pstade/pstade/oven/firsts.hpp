#ifndef PSTADE_OVEN_FIRSTS_HPP
#define PSTADE_OVEN_FIRSTS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This range was originally written by [1].
// Boost.Fusion2 will make this deprecated anyway.
//
// [1] http://d.hatena.ne.jp/y-hamigaki/20060726


#include <boost/mpl/placeholders.hpp> // _1
#include <pstade/at.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/reference_affect.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


namespace firsts_detail {


    template< class PairRange >
    struct baby
    {
        typedef typename
            detail::reference_affect<
                PairRange,
                value_at_first<boost::mpl::_1>
            >::type
        ref_t;

        typedef typename
            boost::result_of<
                op_make_transformed<ref_t>(PairRange&, op_at_first const&)
            >::type
        result;

        result call(PairRange& rng)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<PairRange>));
            return op_make_transformed<ref_t>()(rng, at_first);
        }
    };


} // namespace firsts_detail


PSTADE_FUNCTION(make_firsts, (firsts_detail::baby<_>))
PSTADE_PIPABLE(firsts, (op_make_firsts))


} } // namespace pstade::oven


#endif
