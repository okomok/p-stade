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
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <pstade/in_unnamed.hpp>
#include <pstade/unparenthesize.hpp>
#include "./config.hpp"


#define PSTADE_EGG_OBJECT(F, O) \
    PSTADE_EGG_OBJECT_aux1(PSTADE_UNPARENTHESIZE(F), O) \
/**/


    #define PSTADE_EGG_OBJECT_aux1(F, O) \
        PSTADE_EGG_OBJECT_pod_check(F) \
        PSTADE_EGG_OBJECT_aux2(F, O) \
    /**/


#if !defined(PSTADE_EGG_NO_STATIC_INITIALIZATION)

    #define PSTADE_EGG_OBJECT_aux2(F, O) \
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

    #define PSTADE_EGG_OBJECT_aux2(F, O) \
        F const O \
    /**/

#endif


#if defined(PSTADE_EGG_HAS_IS_POD)
    // msvc says error C2370 in the case of 'BOOST_MPL_ASSERT'.
    #define PSTADE_EGG_OBJECT_pod_check(F) BOOST_STATIC_ASSERT((boost::is_pod< F >::value));
#else
    #define PSTADE_EGG_OBJECT_pod_check(F)
#endif


#endif
