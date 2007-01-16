#ifndef PSTADE_OVEN_POPPED_HPP
#define PSTADE_OVEN_POPPED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// 'rng|applied(pop);' is better?
// But Haskell provides one named 'init' as primitive.


#include <boost/range/begin.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./detail/range_prior.hpp"
#include "./concepts.hpp"
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


namespace popped_detail {


    template< class Range >
    struct baby
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));

        typedef typename
            sub_range_result<Range>::type
        result;

        result call(Range& rng)
        {
            return result(boost::begin(rng), detail::range_prior(rng));
        }
    };


} // namespace popped_detail


PSTADE_FUNCTION(make_popped, (popped_detail::baby<_>))
PSTADE_PIPABLE(popped, (op_make_popped))


} } // namespace pstade::oven


#endif
