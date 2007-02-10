#ifndef PSTADE_OVEN_COPIED_OUT_HPP
#define PSTADE_OVEN_COPIED_OUT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./algorithm.hpp" // copy
#include "./concepts.hpp"


namespace pstade { namespace oven {


namespace copied_out_detail {


    template< class Range, class OutIter >
    struct baby
    {
        typedef
            Range&
        result;

        result call(Range& rng, OutIter& to)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            copy(rng, to);
            return rng;
        }
    };

    PSTADE_FUNCTION(normal, (baby<_, _>))


} // namespace copied_out_detail


PSTADE_PIPABLE(copied_out, (copied_out_detail::op_normal))


} } // namespace pstade::oven


#endif
