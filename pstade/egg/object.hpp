#ifndef PSTADE_EGG_OBJECT_HPP
#define PSTADE_EGG_OBJECT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <pstade/in_unnamed.hpp>
#include <pstade/unparenthesize.hpp>
#include "./detail/config.hpp"


#define PSTADE_EGG_OBJECT(F, O) \
    PSTADE_EGG_OBJECT_aux(PSTADE_UNPARENTHESIZE(F), O) \
/**/


#if !defined(PSTADE_EGG_NO_STATIC_INITIALIZATION)

    #define PSTADE_EGG_OBJECT_aux(F, O) \
        PSTADE_EGG_OBJECT_static_const(O) \
        namespace { \
            PSTADE_IN_UNNAMED F const& O \
                = BOOST_PP_CAT(static_const_of_, O)< F >::value; \
        } \
        PSTADE_EGG_OBJECT_static_const_value(O) \
    /**/

    #define PSTADE_EGG_OBJECT_static_const(O) \
        template<class T> \
        struct BOOST_PP_CAT(static_const_of_, O) \
        { \
            static T const value; \
        }; \
    /**/

    #define PSTADE_EGG_OBJECT_static_const_value(O) \
        template<class T> \
        T const BOOST_PP_CAT(static_const_of_, O)<T>::value \
    /**/

#else

    #define PSTADE_EGG_OBJECT_aux(F, O) \
        F const O \
    /**/

#endif


#endif
