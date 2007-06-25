#ifndef PSTADE_OVEN_RVALUES_HPP
#define PSTADE_OVEN_RVALUES_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./converted.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace rvalues_detail {


    template< class Range >
    struct baby
    {
        typedef typename
            range_value<Range>::type
        value_t;

        typedef typename
            boost::result_of<
                op_make_converted<value_t>(Range&)
            >::type
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return op_make_converted<value_t>()(rng);
        }
    };


} // namespace rvalues_detail


PSTADE_FUNCTION(make_rvalues, (rvalues_detail::baby<_>))
PSTADE_PIPABLE(rvalues, (op_make_rvalues))


} } // namespace pstade::oven


#endif
