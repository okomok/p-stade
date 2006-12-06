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
#include <pstade/pipable.hpp>
#include <pstade/singleton.hpp>
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

struct copy_range_fun :
    to_type_cast_result
{
    template< class From, class Type_To >
    typename to_type<Type_To>::type operator()(From const& from, Type_To) const
    {
        return oven::copy_range<typename to_type<Type_To>::type>(from);
    }
};

PSTADE_SINGLETON_CONST(copy_range_fun, copy_range_)
PSTADE_PIPABLE(copied, boost::result_of<auto_castable_fun(copy_range_fun)>::type)


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
        Result call(Range& rng, OutIter to) const
        {
            oven::copy(rng, to);
            return rng;
        }
    };


} // namespace copied_out_detail


// Which is better name?
PSTADE_PIPABLE(copied_out, egg::function<copied_out_detail::baby>)
PSTADE_PIPABLE(copied_to,  egg::function<copied_out_detail::baby>)


} } // namespace pstade::oven


#endif
