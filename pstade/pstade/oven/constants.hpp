#ifndef PSTADE_OVEN_CONSTANTS_HPP
#define PSTADE_OVEN_CONSTANTS_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./converted.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./detail/constant_reference.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace constants_detail {


    template< class Range >
    struct base
    {
        typedef typename
            detail::constant_reference<
                typename range_iterator<Range>::type
            >::type
        ref_t;

        typedef typename
            result_of<
                X_make_converted<ref_t>(Range&)
            >::type
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return X_make_converted<ref_t>()(rng);
        }
    };


} // namespace constants_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(constants, (constants_detail::base<_>))


} } // namespace pstade::oven


#endif
