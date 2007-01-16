#ifndef PSTADE_OVEN_CLEARED_HPP
#define PSTADE_OVEN_CLEARED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


namespace cleared_detail {


    template< class Range >
    struct baby
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        typedef typename
            sub_range_result<Range>::type
        result;

        result call(Range& rng)
        {
            return result(boost::end(rng), boost::end(rng));
        }
    };


} // namespace cleared_detail


PSTADE_FUNCTION(make_cleared, (cleared_detail::baby<_>))
PSTADE_PIPABLE(cleared, (op_make_cleared))


} } // namespace pstade::oven


#endif
