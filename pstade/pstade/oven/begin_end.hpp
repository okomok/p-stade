#ifndef PSTADE_OVEN_BEGIN_END_HPP
#define PSTADE_OVEN_BEGIN_END_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Provides functor version and pipable interface.


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace begin_end_detail {


    struct with_apply
    {
        template< class Myself, class Range >
        struct apply :
            range_iterator<Range>
        { };
    };


} // namespace begin_end_detail


struct op_begin :
    begin_end_detail::with_apply,
    callable<op_begin>
{
    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return boost::begin(rng);
    }
};

struct op_end   :
    begin_end_detail::with_apply,
    callable<op_end>
{
    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return boost::end(rng);
    }
};


PSTADE_ADL_BARRIER(begin_end) { // for Boost v1.33 'boost::const_begin/end'

PSTADE_CONSTANT(begin, (op_begin))
PSTADE_CONSTANT(end, (op_end))

} // ADL barrier


PSTADE_PIPABLE(begins, (op_begin))
PSTADE_PIPABLE(ends, (op_end))


} } // namespace pstade::oven


#endif
