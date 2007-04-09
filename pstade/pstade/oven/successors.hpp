#ifndef PSTADE_OVEN_SUCCESORS_HPP
#define PSTADE_OVEN_SUCCESORS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./succeed_iterator.hpp"


namespace pstade { namespace oven {


namespace successors_detail {


    template< class Range, class Council >
    struct baby
    {
        typedef
            succeed_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<Council>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, Council& council) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            return result_type(
               iter_t(boost::begin(rng), council, boost::end(rng)),
               iter_t(boost::end(rng),   council, boost::end(rng))
            );
        }
    };


} // namespace successors_detail


PSTADE_FUNCTION(make_successors, (successors_detail::baby<_, _>))
PSTADE_PIPABLE(successors, (op_make_successors))


} } // namespace pstade::oven


#endif

