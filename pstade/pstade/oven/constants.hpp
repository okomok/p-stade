#ifndef PSTADE_OVEN_CONSTANTS_HPP
#define PSTADE_OVEN_CONSTANTS_HPP
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
#include "./detail/constant_reference.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace constants_detail {


    template< class Range >
    struct baby
    {
        typedef typename
            detail::constant_reference<
                typename range_iterator<Range>::type
            >::type
        ref_t;

        typedef typename
            boost::result_of<
                op_make_converted<ref_t>(Range&)
            >::type
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return op_make_converted<ref_t>()(rng);
        }
    };


} // namespace constants_detail


PSTADE_FUNCTION(make_constants, (constants_detail::baby<_>))
PSTADE_PIPABLE(constants, (op_make_constants))


} } // namespace pstade::oven


#endif
