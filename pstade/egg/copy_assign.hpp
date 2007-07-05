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
#include <boost/preprocessor/facilities/identity.hpp>
#include "./auxiliary.hpp"
#include "./function.hpp"


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


        typedef function<baby> op;


    } // namespace copy_assign_detail


    typedef result_of_auxiliary1<copy_assign_detail::op>::type op_copy_assign;
    PSTADE_EGG_OBJECT((op_copy_assign), copy_assign) = PSTADE_EGG_AUXILIARY_RESULT_INITIALIZER(BOOST_PP_IDENTITY({{}}));


} } // namespace pstade::egg


#endif
