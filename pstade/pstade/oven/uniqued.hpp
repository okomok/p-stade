#ifndef PSTADE_OVEN_UNIQUED_HPP
#define PSTADE_OVEN_UNIQUED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/equal_to.hpp>
#include <pstade/egg/not.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/result_of.hpp>
#include "./adjacent_filtered.hpp"
#include "./concepts.hpp"
#include "./detail/baby_to_adaptor.hpp"


namespace pstade { namespace oven {


namespace uniqued_detail {


    struct baby
    {
        template< class Myself, class Range, class BinaryPred = egg::op_equal_to const >
        struct apply :
            result_of<
                op_make_adjacent_filtered(
                    Range&,
                    typename result_of<
                        egg::op_not_(typename pass_by_value<BinaryPred>::type)
                    >::type
                )
            >
        { };

        template< class Result, class Range, class BinaryPred >
        Result call(Range& rng, BinaryPred& pred) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return make_adjacent_filtered(rng, egg::not_(pred));
        }

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            return (*this)(rng, egg::equal_to);
        }
    };


} // namespace uniqued_detail


PSTADE_OVEN_BABY_TO_ADAPTOR(uniqued, (uniqued_detail::baby))


} } // namespace pstade::oven


#endif
