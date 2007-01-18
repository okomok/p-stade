#ifndef PSTADE_OVEN_WINDOW_HPP
#define PSTADE_OVEN_WINDOW_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/next_prior.hpp" // next
#include "./distance.hpp"
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


namespace window_detail {


    template< class Range, class, class >
    struct baby
    {
        typedef typename
            sub_range_result<Range>::type
        result;

        template< class Difference >
        result call(Range& rng, Difference n, Difference m)
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));

            // Should a "bigger" window be allowed?
            // BOOST_ASSERT(0 <= n && n <= m && m <= oven::distance(rng));

            typedef typename result::iterator iter_t;
            iter_t first = detail::next(boost::begin(rng), n);
            return result(first, detail::next(first, m - n));
        }
    };


} // namespace window_detail


PSTADE_FUNCTION(make_window, (window_detail::baby<_, _, _>))
PSTADE_PIPABLE(window, (op_make_window))


} } // namespace pstade::oven


#endif
