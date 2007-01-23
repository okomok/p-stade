#ifndef PSTADE_OVEN_ADVANCED_HPP
#define PSTADE_OVEN_ADVANCED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This range had the name 'shift_range',
// which is reserved to "logical shift operation" for someday.
// 'cshift_range'(cyclic shift operation) is also a candidate. 


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/next_prior.hpp" // next
#include "./distance.hpp"
#include "./range_difference.hpp"
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


namespace advanced_detail {


    template< class Range, class, class >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            sub_range_result<Range>::type
        result;

        result call(Range& rng, diff_t const& dfirst, diff_t const& dlast)
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            BOOST_ASSERT(0 + dfirst <= oven::distance(rng) + dlast);

	        return result(
                detail::next(boost::begin(rng), dfirst),
                detail::next(boost::end(rng), dlast)
            );
        }
    };


} // namespace advanced_detail


PSTADE_FUNCTION(make_advanced, (advanced_detail::baby<_, _, _>))
PSTADE_PIPABLE(advanced, (op_make_advanced))


} } // namespace pstade::oven


#endif
