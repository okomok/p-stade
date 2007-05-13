#ifndef PSTADE_OVEN_FRONT_BACK_HPP
#define PSTADE_OVEN_FRONT_BACK_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/next_prior.hpp> // prior
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/callable.hpp>
#include "./concepts.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace front_back_detail {


    template< template< class > class F >
    struct op_front :
        callable< op_front<F> >
    {
        template< class Myself, class Range >
        struct apply :
            F<Range>
        { };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            BOOST_ASSERT(!boost::empty(rng));

            return *boost::begin(rng);
        }
    };


    template< template< class > class F >
    struct op_back :
        callable< op_back<F> >
    {
        template< class Myself, class Range >
        struct apply :
            F<Range>
        { };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
            BOOST_ASSERT(!boost::empty(rng));

            return *boost::prior(boost::end(rng));
        }
    };


} // namespace front_back_detail


PSTADE_AUXILIARY(0, front,       (front_back_detail::op_front<range_reference>))
PSTADE_AUXILIARY(0, value_front, (front_back_detail::op_front<range_value>))
PSTADE_AUXILIARY(0, back,        (front_back_detail::op_back<range_reference>))
PSTADE_AUXILIARY(0, value_back,  (front_back_detail::op_back<range_value>))


} } // namespace pstade::oven


#endif
