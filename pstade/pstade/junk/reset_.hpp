#ifndef PSTADE_EGG_RESET_HPP
#define PSTADE_EGG_RESET_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>


namespace pstade { namespace egg {


    struct op_reset
    {
        typedef void result_type;

        template<class X, class A>
        void operator()(X& x, A& a) const
        {
            x = X(a);
        }

        template<class X, class A>
        void operator()(X& x, A const& a) const
        {
            x = X(a);
        }

        template<class X>
        void operator()(X& x) const
        {
            x = X();
        }
    };

    PSTADE_POD_CONSTANT((op_reset), reset) = {};


    struct op_move_reset
    {
        typedef void result_type;

        template<class X, class A>
        void operator()(X& x, A a) const
        {
            x = X(a);
        }
    };

    PSTADE_POD_CONSTANT((op_move_reset), move_reset) = {};


} } // namespace pstade::egg


#endif
