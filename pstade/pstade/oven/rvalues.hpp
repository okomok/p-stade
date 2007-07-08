#ifndef PSTADE_OVEN_RVALUES_HPP
#define PSTADE_OVEN_RVALUES_HPP
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
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace rvalues_detail {


    template< class Range >
    struct base
    {
        typedef typename
            range_value<Range>::type
        value_t;

        typedef typename
            result_of<
                xp_make_converted<value_t>(Range&)
            >::type
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return xp_make_converted<value_t>()(rng);
        }
    };


} // namespace rvalues_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(rvalues, (rvalues_detail::base<_>))


} } // namespace pstade::oven


#endif
