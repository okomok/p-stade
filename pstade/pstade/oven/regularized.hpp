#ifndef PSTADE_OVEN_REGULARIZED_HPP
#define PSTADE_OVEN_REGULARIZED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./regularize_iterator.hpp"


namespace pstade { namespace oven {


namespace regularized_detail {


    template< class Range >
    struct baby
    {
        typedef
            regularize_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng)
        {
            // Iterator here can be neither Assignable nor DefaultConstructible.
            // PSTADE_CONCEPT_ASSERT((*Broken*SinglePass<Range>));

            return result(rng);
        }
    };


} // namespace regularized_detail


PSTADE_FUNCTION(make_regularized, (regularized_detail::baby<_>))
PSTADE_PIPABLE(regularized, (op_make_regularized))


} } // namespace pstade::oven


#endif
