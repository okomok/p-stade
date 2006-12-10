#ifndef PSTADE_OVEN_ALWAYS_RANGE_HPP
#define PSTADE_OVEN_ALWAYS_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Unused, class Range >
struct always_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< always_range<Unused, Range> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    always_range(Unused&, Range& rng) :
        super_t(rng)
    { }

    typedef Unused pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_always_range, always_range, (object_by_qualifier)(object_by_qualifier))
PSTADE_PIPABLE(always, op_make_always_range)


} } // namespace pstade::oven


#endif
