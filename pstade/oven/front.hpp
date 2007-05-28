#ifndef PSTADE_OVEN_FRONT_HPP
#define PSTADE_OVEN_FRONT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/prelude.hpp"
#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/callable.hpp>
#include "./concepts.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace front_detail {


    template< template< class > class F >
    struct op :
        callable< op<F> >
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


} // namespace front_detail


PSTADE_AUXILIARY(0, front,       (front_detail::op<range_reference>))
PSTADE_AUXILIARY(0, value_front, (front_detail::op<range_value>))


} } // namespace pstade::oven


#endif
