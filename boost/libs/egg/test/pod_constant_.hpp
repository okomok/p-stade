#ifndef PSTADE_POD_CONSTANT_HPP
#define PSTADE_POD_CONSTANT_HPP



// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://lists.boost.org/Archives/boost/2007/06/123353.php


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/version.hpp>
#include <pstade/in_unnamed.hpp>
#include <pstade/unparenthesize.hpp>


// msvc optimizers can static-initialize, though.
#if 0 // BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
    #define PSTADE_POD_CONSTANT_NO_STATIC_INITIALIZATION
#endif


// Do you know the exact condition?
#if defined(BOOST_MSVC) && defined(_MSC_FULL_VER) && (_MSC_FULL_VER >=140050215)
    #define PSTADE_POD_CONSTANT_HAS_IS_POD
#endif


#define PSTADE_POD_CONSTANT(F, O) \
    PSTADE_POD_CONSTANT_aux1(PSTADE_UNPARENTHESIZE(F), O) \
/**/


    #define PSTADE_POD_CONSTANT_aux1(F, O) \
        PSTADE_POD_CONSTANT_pod_check(F) \
        PSTADE_POD_CONSTANT_aux2(F, O) \
    /**/


#if !defined(PSTADE_POD_CONSTANT_NO_STATIC_INITIALIZATION)

    #define PSTADE_POD_CONSTANT_aux2(F, O) \
        template<class T> \
        struct BOOST_PP_CAT(static_const_of_, O) \
        { \
            static T const value; \
        }; \
        namespace { \
            PSTADE_IN_UNNAMED F const& O \
                = BOOST_PP_CAT(static_const_of_, O)< F >::value; \
        } \
        template<class T> \
        T const BOOST_PP_CAT(static_const_of_, O)<T>::value \
    /**/

#else

    #define PSTADE_POD_CONSTANT_aux2(F, O) \
        F const O \
    /**/

#endif


#if defined(PSTADE_POD_CONSTANT_HAS_IS_POD)
    // msvc says error C2370 in the case of 'BOOST_MPL_ASSERT'.
    #define PSTADE_POD_CONSTANT_pod_check(F) BOOST_STATIC_ASSERT((boost::is_pod< F >::value));
#else
    #define PSTADE_POD_CONSTANT_pod_check(F)
#endif


#endif
