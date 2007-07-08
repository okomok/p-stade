#ifndef PSTADE_OVEN_CLEARED_HPP
#define PSTADE_OVEN_CLEARED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/end.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace cleared_detail {


    template< class Range >
    struct base
    {
        typedef typename
            iter_range_of<Range>::type const
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return aux(boost::end(rng));
        }

        template< class Iterator >
        result_type aux(Iterator last) const
        {
            return result_type(last, last);
        }
    };


} // namespace cleared_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(cleared, (cleared_detail::base<_>))


} } // namespace pstade::oven


#endif
