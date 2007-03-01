#ifndef PSTADE_OVEN_DROPPED_HPP
#define PSTADE_OVEN_DROPPED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // min
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_traversal.hpp"


namespace pstade { namespace oven {


namespace dropped_detail {


    template< class Result, class Iterator, class Difference > inline
    Result aux(Iterator first, Iterator const& last, Difference d,
        boost::random_access_traversal_tag)
    {
        return Result(first + (std::min)(last - first, d), last);
    }

    template< class Result, class Iterator, class Difference >
    Result aux(Iterator first, Iterator const& last, Difference d,
        boost::single_pass_traversal_tag)
    {
        while (first != last && d != 0) {
            ++first; --d;
        }

        return Result(first, last);
    }


    template< class Range, class >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            iter_range_of<Range>::type const
        result_type;

        result_type operator()(Range& rng, diff_t const& d) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            BOOST_ASSERT(0 <= d);

            return dropped_detail::aux<result_type>(
                boost::begin(rng), boost::end(rng), d,
                typename range_traversal<Range>::type()
            );
        }
    };


} // namespace dropped_detail


PSTADE_FUNCTION(make_dropped, (dropped_detail::baby<_, _>))
PSTADE_PIPABLE(dropped, (op_make_dropped))


} } // namespace pstade::oven


#endif
