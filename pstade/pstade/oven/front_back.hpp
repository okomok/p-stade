#ifndef PSTADE_OVEN_FRONT_BACK_HPP
#define PSTADE_OVEN_FRONT_BACK_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// They can't return the references;
// http://std.dkuug.dk/jtc1/sc22/wg21/docs/lwg-defects.html#198
//
// '*boost::begin(rng)' and '*boost::prior(rng)' can return reference.


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/function.hpp>
#include "./concepts.hpp"
#include "./detail/next_prior.hpp" // prior
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace front_back_detail {


    template< class Range >
    struct baby_front
    {
        typedef typename
            range_value<Range>::type
        result;

        result call(Range& rng)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return *boost::begin(rng);
        }
    };


    template< class Range >
    struct baby_back
    {
        typedef typename
            range_value<Range>::type
        result;

        result call(Range& rng)
        {
            PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
            return *detail::prior(boost::end(rng));
        }
    };


    PSTADE_FUNCTION(normal_front, (baby_front<_>))
    PSTADE_FUNCTION(normal_back,  (baby_back<_>))


} // namespace front_back_detail


PSTADE_AUXILIARY0(front, (front_back_detail::op_normal_front))
PSTADE_AUXILIARY0(back,  (front_back_detail::op_normal_back))


} } // namespace pstade::oven


#endif
