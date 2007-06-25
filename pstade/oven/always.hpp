#ifndef PSTADE_OVEN_ALWAYS_HPP
#define PSTADE_OVEN_ALWAYS_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace always_detail {


    template< class Unused, class Range >
    struct baby
    {
        typedef typename
            iter_range_of<Range>::type const
        result_type;

        result_type operator()(Unused&, Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return result_type(rng);
        }
    };


} // namespace always_detail


PSTADE_FUNCTION(make_always, (always_detail::baby<_, _>))
PSTADE_PIPABLE(always, (op_make_always))


} } // namespace pstade::oven


#endif
