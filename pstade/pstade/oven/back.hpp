#ifndef PSTADE_OVEN_BACK_HPP
#define PSTADE_OVEN_BACK_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/prelude.hpp"
#include <boost/assert.hpp>
#include <boost/next_prior.hpp> // prior
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/callable.hpp>
#include "./concepts.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace back_detail {


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
            PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
            BOOST_ASSERT(!boost::empty(rng));

            return *boost::prior(boost::end(rng));
        }
    };


} // namespace back_detail


PSTADE_AUXILIARY(0, back,        (back_detail::op<range_reference>))
PSTADE_AUXILIARY(0, value_back,  (back_detail::op<range_value>))


} } // namespace pstade::oven


#endif
