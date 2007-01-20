#ifndef PSTADE_OVEN_COPIED_OUT_HPP
#define PSTADE_OVEN_COPIED_OUT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/callable.hpp>
#include <pstade/pipable.hpp>
#include "./algorithm.hpp" // copy
#include "./concepts.hpp"


namespace pstade { namespace oven {


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
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        oven::copy(rng, to);
        return rng;
    }
};


// Which is better name?
PSTADE_PIPABLE(copied_out, (op_copied_out))
PSTADE_PIPABLE(copied_to,  (op_copied_out))


} } // namespace pstade::oven


#endif
