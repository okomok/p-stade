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
#include "./forward.hpp"


namespace pstade { namespace egg {


    namespace identity_detail {


        template<class Strategy>
        struct little
        {
            template<class Myself, class X>
            struct apply :
                result_of_forward<Strategy, 0, X>
            { };

            template<class Result, class X>
            Result call(X& x) const
            {
                return egg::forward<Strategy, 0>(x);
            }
        };


    } // namespace identity_detail


    template<class Strategy = by_perfect>
    struct X_identity :
        function<identity_detail::little<Strategy>, Strategy>
    { };

    typedef X_identity<>::function_type T_identity;
    PSTADE_ADL_BARRIER(identity) {
        PSTADE_POD_CONSTANT((T_identity), identity) = {{}};
    }


} } // namespace pstade::egg


#endif
