#ifndef PSTADE_OVEN_WINDOW_HPP
#define PSTADE_OVEN_WINDOW_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./advance_from.hpp"
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_iterator.hpp"
#include "./traversal_tags.hpp" // is_bidirectional


namespace pstade { namespace oven {


namespace window_detail {


    template< class Range >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            range_iterator<Range>::type
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, diff_t n, diff_t m) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            BOOST_ASSERT(n <= m);
            BOOST_ASSERT(n < 0 ? is_bidirectional(rng) : true);

            // A "bigger" window is allowed.
            // 'n < 0' or 'distance(rng) < m' is ok.

            iter_t first = advance_from(boost::begin(rng), n);
            return result_type(first, advance_from(first, m - n));
        }
    };


} // namespace window_detail


PSTADE_FUNCTION(make_window, (window_detail::baby<_>))
PSTADE_PIPABLE(window, (op_make_window))


} } // namespace pstade::oven


#endif
