#ifndef PSTADE_OVEN_AT_HPP
#define PSTADE_OVEN_AT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/callable.hpp>
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./range_difference.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace at_detail {


    template< class Lambda >
    struct op :
        callable< op<Lambda> >
    {
        template< class Myself, class Range, class Difference >
        struct apply :
            boost::mpl::apply1<Lambda, Range>
        { };

        template< class Result, class Range >
        Result call(Range& rng, typename range_difference<Range>::type const& d) const
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
            BOOST_ASSERT(0 <= d && d < distance(rng));
            return *(boost::begin(rng) + d);
        }
    };


    struct msvc8_op :
        op< range_reference<boost::mpl::_> >
    { };

    struct msvc8_value_op  :
        op< range_value<boost::mpl::_> >
    { };
    

} // namespace at_detail


PSTADE_AUXILIARY(1, at,       (at_detail::msvc8_op))
PSTADE_AUXILIARY(1, value_at, (at_detail::msvc8_value_op))


} } // namespace pstade::oven


#endif
