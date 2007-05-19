#ifndef PSTADE_OVEN_PARTITIONED_HPP
#define PSTADE_OVEN_PARTITIONED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <utility> // pair
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/functional.hpp> // not_
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./filtered.hpp"


namespace pstade { namespace oven {


namespace partitioned_detail {


    template< class Range, class Predicate >
    struct baby
    {
        typedef typename
            boost::result_of<
                op_make_filtered(Range&, Predicate&)
            >::type
        rng1_t;

        typedef typename
            boost::result_of<
                op_make_filtered(Range&, typename boost::result_of<op_not(Predicate&)>::type)
            >::type
        rng2_t;

        typedef
            std::pair<rng1_t, rng2_t> const
        result_type;

        result_type operator()(Range& rng, Predicate& pred) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));

            return result_type(
                make_filtered(rng, pred),
                make_filtered(rng, not_(pred))
            );
        }
    };


} // namespace partitioned_detail


PSTADE_FUNCTION(make_partitioned, (partitioned_detail::baby<_, _>))
PSTADE_PIPABLE(partitioned, (op_make_partitioned))


} } // namespace pstade::oven


#endif
