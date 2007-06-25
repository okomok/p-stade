#ifndef PSTADE_OVEN_RECURSION_HPP
#define PSTADE_OVEN_RECURSION_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/function.hpp>
#include "./concepts.hpp"
#include "./detail/lazy_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace recursion_detail {


    template< class Range >
    struct baby
    {
        typedef
            detail::lazy_iterator<Range>
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            return result_type(iter_t(rng, false), iter_t(rng, true));
        }
    };


} // recursion_detail


PSTADE_FUNCTION(recursion, (recursion_detail::baby<_>))


} } // namespace pstade::oven


#endif
