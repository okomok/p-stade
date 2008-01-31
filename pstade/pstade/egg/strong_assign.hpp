#ifndef PSTADE_EGG_STRONG_ASSIGN_HPP
#define PSTADE_EGG_STRONG_ASSIGN_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./ambi.hpp"
#include "./do_swap.hpp"
#include "./function.hpp"


namespace pstade { namespace egg {


    namespace strong_assign_detail {


        struct little
        {
            template<class Me, class To, class From>
            struct apply
            {
                typedef To& type;
            };

            template<class Re, class To, class From>
            Re call(To& to, From& from) const
            {
                To tmp = from;
                do_swap(to, tmp);
                return to;
            }
        };


    } // namespace strong_assign_detail


    typedef result_of_ambi1< function<strong_assign_detail::little> >::type T_strong_assign;
    PSTADE_POD_CONSTANT((T_strong_assign), strong_assign) = PSTADE_EGG_AMBI({{}});


} } // namespace pstade::egg


#endif
