#ifndef PSTADE_OVEN_ALWAYS_HPP
#define PSTADE_OVEN_ALWAYS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


namespace always_detail {


    template< class Unused, class Range >
    struct baby
    {
        typedef typename
            sub_range_result<Range>::type
        result;

        result call(Unused&, Range& rng)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return result(rng);
        }
    };


} // namespace always_detail


PSTADE_FUNCTION(make_always, (always_detail::baby<_, _>))
PSTADE_PIPABLE(always, (op_make_always))


} } // namespace pstade::oven


#endif
