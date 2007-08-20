#ifndef PSTADE_OVEN_RECURSION_HPP
#define PSTADE_OVEN_RECURSION_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/adapt.hpp>
#include <pstade/pod_constant.hpp>
#include "./concepts.hpp"
#include "./detail/lazy_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace recursion_detail {


    template< class Range >
    struct base
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


typedef PSTADE_EGG_ADAPT((recursion_detail::base<boost::mpl::_>)) op_recursion;
PSTADE_POD_CONSTANT((op_recursion), recursion) = PSTADE_EGG_ADAPT_TYPE;


} } // namespace pstade::oven


#endif
