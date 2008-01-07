#ifndef PSTADE_EGG_IDENTITY_HPP
#define PSTADE_EGG_IDENTITY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"


namespace pstade { namespace egg {


    namespace identity_detail {


        struct little
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


    typedef function<identity_detail::little, by_perfect> T_identity;
    PSTADE_ADL_BARRIER(identity) { // for std
        PSTADE_POD_CONSTANT((T_identity), identity) = {{}};
    }


} } // namespace pstade::egg


#endif
