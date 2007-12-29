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
#include "./ambi.hpp"
#include "./do_swap.hpp"
#include "./by_perfect.hpp"


namespace pstade { namespace egg {


    namespace strong_assign_detail {


        struct baby
        {
            template<class Myself, class To, class From>
            struct apply
            {
                typedef To& type;
            };

            template<class Result, class To, class From>
            Result call(To& to, From& from) const
            {
                To tmp = from;
                do_swap(to, tmp);
                return to;
            }
        };


        typedef function<baby, by_perfect> op;


    } // namespace strong_assign_detail


    typedef result_of_ambi1<strong_assign_detail::op>::type T_strong_assign;
    PSTADE_POD_CONSTANT((T_strong_assign), strong_assign) = PSTADE_EGG_AMBI_L {{}} PSTADE_EGG_AMBI_R;


} } // namespace pstade::egg


#endif
