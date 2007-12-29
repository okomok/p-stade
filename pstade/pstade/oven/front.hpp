#ifndef PSTADE_OVEN_FRONT_HPP
#define PSTADE_OVEN_FRONT_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <pstade/egg/ambi.hpp>
#include <pstade/egg/function.hpp>
#include "./concepts.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace front_detail {


    template< template< class > class F >
    struct baby
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


    typedef egg::function< baby<range_reference> > op;
    typedef egg::function< baby<range_value> > value_op;


} // namespace front_detail


typedef egg::result_of_ambi0<front_detail::op>::type T_front;
PSTADE_POD_CONSTANT((T_front), front) = PSTADE_EGG_AMBI_L {{}} PSTADE_EGG_AMBI_R;

typedef egg::result_of_ambi0<front_detail::value_op>::type T_value_front;
PSTADE_POD_CONSTANT((T_value_front), value_front) = PSTADE_EGG_AMBI_L {{}} PSTADE_EGG_AMBI_R;


} } // namespace pstade::oven


#endif
