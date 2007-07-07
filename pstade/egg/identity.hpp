#ifndef PSTADE_EGG_IDENTITY_HPP
#define PSTADE_EGG_IDENTITY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>
#include "./function.hpp"


namespace pstade { namespace egg {


    namespace identity_detail {


        struct baby
        {
            template<class Myself, class X>
            struct apply
            {
                typedef X& type;
            };

            template<class Result, class X>
            Result call(X& x) const
            {
                return x;
            }
        };


    } // namespace identity_detail


    typedef function<identity_detail::baby> op_identity;
    PSTADE_ADL_BARRIER(identity) { // for 'std'
        PSTADE_POD_CONSTANT((op_identity), identity) = { {} };
    }


} } // namespace pstade::egg


#endif
