#ifndef PSTADE_EGG_SWAP_ASSIGN_HPP
#define PSTADE_EGG_SWAP_ASSIGN_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Force exception-safe copy-assignment using swap.


#include <pstade/pod_constant.hpp>
#include "./auxiliary.hpp"
#include "./do_swap.hpp"
#include "./function.hpp"


namespace pstade { namespace egg {


    namespace swap_assign_detail {


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
                To tmp = from; // copy-initialization
                do_swap(tmp, to);
                return to;
            }
        };


        typedef function<baby> op;


    } // namespace swap_assign_detail


    typedef result_of_auxiliary1<swap_assign_detail::op>::type op_swap_assign;
    PSTADE_POD_CONSTANT((op_swap_assign), swap_assign) = PSTADE_EGG_AUXILIARY_L {{}} PSTADE_EGG_AUXILIARY_R;


} } // namespace pstade::egg


#endif
