#ifndef PSTADE_EGG_COPY_ASSIGN_HPP
#define PSTADE_EGG_COPY_ASSIGN_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// The ambiguity buster; call copy-assignment explicitly.


#include <pstade/pod_constant.hpp>
#include "./ambi.hpp"
#include "./by_perfect.hpp"
#include "./copy.hpp"
#include "./move_assign.hpp"


namespace pstade { namespace egg {


    namespace copy_assign_detail {


        struct little
        {
            template<class Me, class To, class From>
            struct apply
            {
                typedef To &type;
            };

            template<class Re, class To, class From>
            Re call(To &to, From &from) const
            {
                move_assign(egg::copy<To>(from), to);
                return to;
            }
        };


    } // namespace copy_assign_detail


    typedef result_of_ambi1<function<copy_assign_detail::little>, by_perfect>::type T_copy_assign;
    PSTADE_POD_CONSTANT((T_copy_assign), copy_assign) = PSTADE_EGG_AMBI({{}});


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
