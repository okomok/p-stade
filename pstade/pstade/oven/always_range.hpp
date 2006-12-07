#ifndef PSTADE_OVEN_ALWAYS_RANGE_HPP
#define PSTADE_OVEN_ALWAYS_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct always_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< always_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    template< class Unused >
    always_range(Unused const&, Range& rng) :
        super_t(rng)
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace always_range_detail {


    struct baby_make
    {
        template< class Myself, class Unused, class Range >
        struct apply
        {
            typedef always_range<Range> const type;
        };

        template< class Result, class Unused, class Range>
        Result call(Unused& _, Range& rng) const
        {
            return Result(_, rng);
        }
    };


} // namespace always_range_detail


PSTADE_EGG_FUNCTION(make_always_range, always_range_detail::baby_make)
PSTADE_PIPABLE(always, op_make_always_range)


} } // namespace pstade::oven


#endif
