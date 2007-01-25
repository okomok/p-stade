#ifndef PSTADE_OVEN_NULL_TERMINATED_HPP
#define PSTADE_OVEN_NULL_TERMINATED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // find
#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/function.hpp>
#include <pstade/functional.hpp> // not_, equal_to_0
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./range_iterator.hpp"
#include "./taken_while.hpp"


namespace pstade { namespace oven {


template< class Range >
PSTADE_CONCEPT_WHERE(
    ((Forward<Range>)), // ((Readable<PSTADE_DEDUCED_CONST(Range)>)),
(bool)) is_null_terminated(Range const& rng)
{
    typedef typename range_iterator<PSTADE_DEDUCED_CONST(Range)>::type iter_t;

    iter_t first = boost::begin(rng);
    iter_t last = boost::end(rng);
    iter_t it = std::find(first, last, 0);

    return it != last;
}


template< class Range > inline
void null_terminate(Range& rng)
{
    BOOST_ASSERT(!boost::empty(rng));
    *boost::begin(rng) = 0;
}


namespace null_terminated_detail {


    template< class Range >
    struct baby
    {
        typedef typename
            boost::result_of<
                op_make_taken_while(Range&, typename boost::result_of<op_not(op_equal_to_0 const&)>::type)
            >::type
        result;

        result call(Range& rng)
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            // PSTADE_CONCEPT_ASSERT((Readable<Range>));

            BOOST_ASSERT(oven::is_null_terminated(rng));
            return make_taken_while(rng, not_(equal_to_0));
        }
    };


} // namespace null_terminated_detail


PSTADE_FUNCTION(make_null_terminated, (null_terminated_detail::baby<_>))
PSTADE_PIPABLE(null_terminated, (op_make_null_terminated))


} } // namespace pstade::oven


#endif
