#ifndef PSTADE_OVEN_COPY_RANGE_HPP
#define PSTADE_OVEN_COPY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/auto_castable.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include <pstade/to_type.hpp>
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

struct op_copy_range :
    to_type_cast_result
{
    template< class From, class Type_To >
    typename to_type<Type_To>::type operator()(From const& from, Type_To) const
    {
        return oven::copy_range<typename to_type<Type_To>::type>(from);
    }
};

PSTADE_CONSTANT(copy_range_, op_copy_range)
PSTADE_PIPABLE(copied, boost::result_of<op_auto_castable(op_copy_range)>::type)


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
    Result call(Range& rng, OutIter to) const
    {
        oven::copy(rng, to);
        return rng;
    }
};


// Which is better name?
PSTADE_PIPABLE(copied_out, op_copied_out)
PSTADE_PIPABLE(copied_to,  op_copied_out)


} } // namespace pstade::oven


#endif
