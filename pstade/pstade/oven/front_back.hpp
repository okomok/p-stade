#ifndef PSTADE_OVEN_FRONT_BACK_HPP
#define PSTADE_OVEN_FRONT_BACK_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/callable.hpp>
#include "./concepts.hpp"
#include "./next_prior.hpp" // prior
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace front_back_detail {


    template< class Lambda >
    struct op_front :
        callable< op_front<Lambda> >
    {
        template< class Myself, class Range >
        struct apply :
            boost::mpl::apply1<Lambda, Range>
        { };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            BOOST_ASSERT(!boost::empty(rng));
            return *boost::begin(rng);
        }
    };


    template< class Lambda >
    struct op_back :
        callable< op_back<Lambda> >
    {
        template< class Myself, class Range >
        struct apply :
            boost::mpl::apply1<Lambda, Range>
        { };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
            BOOST_ASSERT(!boost::empty(rng));
            return *prior(boost::end(rng));
        }
    };


    struct msvc8_op_front :
        op_front< range_reference< boost::mpl::_> >
    { };

    struct msvc8_op_back :
        op_back<  range_reference< boost::mpl::_> >
    { };

    struct msvc8_op_value_front :
        op_front< range_value<boost::mpl::_> >
    { };

    struct msvc8_op_value_back :
        op_back<  range_value<boost::mpl::_> >
    { };


} // namespace front_back_detail


PSTADE_AUXILIARY(0, front,       (front_back_detail::msvc8_op_front))
PSTADE_AUXILIARY(0, back,        (front_back_detail::msvc8_op_back))
PSTADE_AUXILIARY(0, value_front, (front_back_detail::msvc8_op_value_front))
PSTADE_AUXILIARY(0, value_back,  (front_back_detail::msvc8_op_value_back))


} } // namespace pstade::oven


#endif
