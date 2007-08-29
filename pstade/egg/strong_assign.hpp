#ifndef PSTADE_EGG_STRONG_ASSIGN_HPP
#define PSTADE_EGG_STRONG_ASSIGN_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./auxiliary.hpp"
#include "./do_swap.hpp"
#include "./function.hpp"


namespace pstade { namespace egg {


    namespace strong_assign_detail {


        struct baby
        {
            template<class Myself, class To, class From>
            struct apply
            {
                typedef To& type;
            };

            template<class Result, class To>
            Result call(To& to, To from) const // copy-initialization for automatic object.
            {
                do_swap(to, from);
                return to;
            }
        };


        typedef function<baby> op;


    } // namespace strong_assign_detail


    typedef result_of_auxiliary1<strong_assign_detail::op>::type op_strong_assign;
    PSTADE_POD_CONSTANT((op_strong_assign), strong_assign) = PSTADE_EGG_AUXILIARY_L {{}} PSTADE_EGG_AUXILIARY_R;


} } // namespace pstade::egg


#endif
