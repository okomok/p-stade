#ifndef PSTADE_OVEN_OUTDIRECTED_HPP
#define PSTADE_OVEN_OUTDIRECTED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./counting.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace outdirected_detail {


    template< class Range >
    struct base
    {
        typedef typename
            range_iterator<Range>::type
        iter_t;

        typedef typename
            result_of<
                T_counting(iter_t, iter_t)
            >::type
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return counting(boost::begin(rng), boost::end(rng));
        }
    };


} // namespace outdirected_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(outdirected, (outdirected_detail::base<_>))


} } // namespace pstade::oven


#endif
