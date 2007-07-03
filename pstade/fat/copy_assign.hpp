#ifndef PSTADE_FAT_COPY_ASSIGN_HPP
#define PSTADE_FAT_COPY_ASSIGN_HPP
#include "./detail/prefix.hpp"


// PStade.Fat
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// The ambiguity buster; call copy-assignment explicitly.


#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/implicit_cast.hpp>
#include <pstade/egg/auxiliary.hpp>
#include <pstade/egg/function.hpp>


namespace pstade { namespace fat {


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


        typedef egg::function<baby> op;


    } // namespace copy_assign_detail


    typedef egg::result_of_auxiliary1<copy_assign_detail::op>::type op_copy_assign;
    PSTADE_EGG_OBJECT((op_copy_assign), copy_assign) = PSTADE_EGG_AUXILIARY_RESULT_INITIALIZER(BOOST_PP_IDENTITY({{}}));


} } // namespace pstade::fat


#endif
