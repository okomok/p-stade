#ifndef PSTADE_EGG_COPY_ASSIGN_HPP
#define PSTADE_EGG_COPY_ASSIGN_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// The ambiguity buster; call copy-assignment explicitly.


#include <boost/implicit_cast.hpp>
#include <pstade/pod_constant.hpp>
#include "./auxiliary.hpp"
#include "./by_perfect.hpp"


namespace pstade { namespace egg {


    namespace copy_assign_detail {


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
                to = boost::implicit_cast<To const&>(from);
                return to;
            }
        };


        typedef function<baby, by_perfect> op;


    } // namespace copy_assign_detail


    typedef result_of_auxiliary1<copy_assign_detail::op>::type op_copy_assign;
    PSTADE_POD_CONSTANT((op_copy_assign), copy_assign) = PSTADE_EGG_AUXILIARY_L {{}} PSTADE_EGG_AUXILIARY_R;


} } // namespace pstade::egg


#endif
