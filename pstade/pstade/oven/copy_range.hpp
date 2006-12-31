#ifndef PSTADE_OVEN_COPY_RANGE_HPP
#define PSTADE_OVEN_COPY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include <pstade/automatic.hpp>
#include <pstade/callable.hpp>
#include <pstade/pipable.hpp>
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

template< class To >
struct op_copy_range
{
    typedef To result_type;

    template< class From >
    To operator()(From const& from) const
    {
        return oven::copy_range<To>(from);
    }
};

PSTADE_PIPABLE(copied, (automatic< op_copy_range<boost::mpl::_1> >))


// copied_out
//

struct op_copied_out :
    callable<op_copied_out>
{
    template< class Myself, class Range, class OutIter >
    struct apply
    {
        typedef Range& type;
    };

    template< class Result, class Range, class OutIter >
    Result call(Range& rng, OutIter& to) const
    {
        oven::copy(rng, to);
        return rng;
    }
};


// Which is better name?
PSTADE_PIPABLE(copied_out, (op_copied_out))
PSTADE_PIPABLE(copied_to, ( op_copied_out))


} } // namespace pstade::oven


#endif
