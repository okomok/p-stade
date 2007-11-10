#ifndef PSTADE_OVEN_CONVERTED_HPP
#define PSTADE_OVEN_CONVERTED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/egg/identity.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/egg/specified.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


template< class To >
struct pod_of_make_converted
{
    struct baby
    {
        template< class Myself, class Range >
        struct apply :
            result_of<
                X_make_transformed<To>(Range&, egg::T_identity const&)
            >
        { };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return X_make_transformed<To>()(rng, egg::identity);
        }
    };

    typedef egg::function<baby> type;
};


template< class To >
struct X_make_converted :
    pod_of_make_converted<To>::type
{ };


PSTADE_EGG_SPECIFIED1(make_converted, X_make_converted, (class))


template< class To >
struct converted :
    egg::result_of_pipable<typename pod_of_make_converted<To>::type>::type,
    egg::lookup_pipable_operator
{ };


} } // namespace pstade::oven


#endif
