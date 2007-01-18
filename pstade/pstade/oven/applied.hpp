#ifndef PSTADE_OVEN_APPLIED_HPP
#define PSTADE_OVEN_APPLIED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Will be cute with the upcoming Boost.Phoenix2.


#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


struct op_make_applied :
    callable<op_make_applied>
{
    template< class Myself, class Range, class, class = void >
    struct apply :
        sub_range_result<Range>
    { };

    template< class Result, class Range, class Begin, class End >
    Result call(Range& rng, Begin& begin, End& end) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        return Result(begin(rng), end(rng));
    }

    template< class Result, class Range, class MakeRange >
    Result call(Range& rng, MakeRange& make) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        return Result(make(rng));
    }
};


PSTADE_CONSTANT(make_applied, (op_make_applied))
PSTADE_PIPABLE(applied, (op_make_applied))


} } // namespace pstade::oven


// for Boost.Phoenix2
//
#if defined(PSTADE_OVEN_USING_PHOENIX_V2)

    #include <boost/spirit/phoenix/core/argument.hpp>
    #include <pstade/constant.hpp>

    namespace pstade { namespace oven {

    PSTADE_CONSTANT(rng1, (boost::phoenix::actor< boost::phoenix::argument<0> >))

    } } // namespace pstade::oven

#endif


#endif
