#ifndef PSTADE_OVEN_COPY_RANGE_HPP
#define PSTADE_OVEN_COPY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include <pstade/egg/baby_auto.hpp>
#include <pstade/egg/pipable.hpp>
#include "./algorithm.hpp" // copy
#include "./extension.hpp"


namespace pstade { namespace oven {


// copy_range
//

PSTADE_ADL_BARRIER(copy_range) { // for Boost


    template< class OvenCopyableRange, class Range > inline
    OvenCopyableRange const
    copy_range(Range const& rng)
    {
        return pstade_oven_extension::Range<OvenCopyableRange>().
            template copy<OvenCopyableRange>(rng);
    }


} // ADL barrier


// copied
//

struct copy_range_class
{
    template< class OvenCopyableRange, class Range >
    static OvenCopyableRange call(Range const& rng)
    {
        return oven::copy_range<OvenCopyableRange>(rng);
    }
};

PSTADE_EGG_PIPABLE(copied, egg::baby_auto<copy_range_class>)


// copied_out
//

namespace copied_out_detail {


    struct baby
    {
        template< class Myself, class Range, class OutIter >
        struct apply
        {
            typedef Range& type;
        };

        template< class Result, class Range, class OutIter >
        Result call(Range& rng, OutIter to)
        {
            oven::copy(rng, to);
            return rng;
        }
    };


} // namespace copied_out_detail


// Which is better name?
PSTADE_EGG_PIPABLE(copied_out, copied_out_detail::baby)
PSTADE_EGG_PIPABLE(copied_to,  copied_out_detail::baby)


} } // namespace pstade::oven


#endif
