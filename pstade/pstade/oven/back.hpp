#ifndef PSTADE_OVEN_BACK_HPP
#define PSTADE_OVEN_BACK_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/next_prior.hpp> // prior
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/auxiliary.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include "./concepts.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace back_detail {


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
            PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
            BOOST_ASSERT(!boost::empty(rng));

            return *boost::prior(boost::end(rng));
        }
    };


    typedef egg::function< baby<range_reference> > op;
    typedef egg::function< baby<range_value> > value_op;


} // namespace back_detail


typedef egg::result_of_auxiliary0<back_detail::op>::type op_back;
PSTADE_POD_CONSTANT((op_back), back) = PSTADE_EGG_AUXILIARY_RESULT_INITIALIZER(BOOST_PP_IDENTITY({{}}));

typedef egg::result_of_auxiliary0<back_detail::value_op>::type op_value_back;
PSTADE_POD_CONSTANT((op_value_back), value_back) = PSTADE_EGG_AUXILIARY_RESULT_INITIALIZER(BOOST_PP_IDENTITY({{}}));


} } // namespace pstade::oven


#endif
