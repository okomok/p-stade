#ifndef PSTADE_OVEN_UNIQUED_HPP
#define PSTADE_OVEN_UNIQUED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/functional.hpp> // equal_to, not_
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/result_of.hpp>
#include "./adjacent_filtered.hpp"
#include "./concepts.hpp"


namespace pstade { namespace oven {


struct op_make_uniqued :
    callable<op_make_uniqued>
{
    template< class Myself, class Range, class BinaryPred = op_equal_to const >
    struct apply :
        result_of<
            op_make_adjacent_filtered(
                Range&,
                typename result_of<
                    op_not_(typename pass_by_value<BinaryPred>::type)
                >::type
            )
        >
    { };

    template< class Result, class Range, class BinaryPred >
    Result call(Range& rng, BinaryPred& pred) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        return make_adjacent_filtered(rng, not_(pred));
    }

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return (*this)(rng, equal_to);
    }
};


PSTADE_CONSTANT(make_uniqued, (op_make_uniqued))
PSTADE_PIPABLE(uniqued, (op_make_uniqued))


} } // namespace pstade::oven


#endif
