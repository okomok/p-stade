#ifndef PSTADE_OVEN_AT_HPP
#define PSTADE_OVEN_AT_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Though 'value_at(rng)' is the same as 'at(rng|rvalues)',
// it should be a primitive function.


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <pstade/egg/ambi.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./range_difference.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace at_detail {


    template< template< class > class F >
    struct baby
    {
        template< class Myself, class Range, class Difference >
        struct apply :
            F<Range>
        { };

        template< class Result, class Range >
        Result call(Range& rng, typename range_difference<Range>::type n) const
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
            BOOST_ASSERT(0 <= n && n < distance(rng));

            return *(boost::begin(rng) + n);
        }
    };


    typedef egg::function< baby<range_reference> > op;
    typedef egg::function< baby<range_value> > value_op;


} // namespace at_detail


typedef egg::result_of_ambi1<at_detail::op>::type T_at;
PSTADE_POD_CONSTANT((T_at), at) = PSTADE_EGG_AMBI_L {{}} PSTADE_EGG_AMBI_R;

typedef egg::result_of_ambi1<at_detail::value_op>::type T_value_at;
PSTADE_POD_CONSTANT((T_value_at), value_at) = PSTADE_EGG_AMBI_L {{}} PSTADE_EGG_AMBI_R;


} } // namespace pstade::oven


#endif
