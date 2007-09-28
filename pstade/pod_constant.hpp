#ifndef PSTADE_POD_CONSTANT_HPP
#define PSTADE_POD_CONSTANT_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// After all, ODR violation workaround:
//   http://lists.boost.org/Archives/boost/2007/06/123353.php
// was given up.
// Even gcc is broken around "address constant expression".


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/cat.hpp>
#include <pstade/unparenthesize.hpp>


namespace pstade { namespace pod_constant_detail {

    // Some compilers can warn if non-POD passed through ellipsis.
    inline void must_be_pod(...) { }

} }


// Do you know the exact condition?
#if defined(BOOST_MSVC) && defined(_MSC_FULL_VER) && (_MSC_FULL_VER >=140050215)
    #include <boost/static_assert.hpp>
    #include <boost/type_traits/is_pod.hpp>
    #define PSTADE_POD_CONSTANT_has_is_pod
#endif


#define PSTADE_POD_CONSTANT(F, O) \
    PSTADE_POD_CONSTANT_aux1(PSTADE_UNPARENTHESIZE(F), O) \
/**/

    #define PSTADE_POD_CONSTANT_aux1(F, O) \
        PSTADE_POD_CONSTANT_pod_check(F, O) \
        PSTADE_POD_CONSTANT_aux2(F, O) \
    /**/

    #define PSTADE_POD_CONSTANT_aux2(F, O) \
        F const PSTADE_POD_CONSTANT_unused O \
    /**/


#if defined(PSTADE_POD_CONSTANT_has_is_pod)

    // 'BOOST_MPL_ASSERT' would cause error C2370 under msvc.
    #define PSTADE_POD_CONSTANT_pod_check(F, O) \
        BOOST_STATIC_ASSERT((boost::is_pod< F >::value)); \
    /**/

#else

    #define PSTADE_POD_CONSTANT_pod_check(F, O) \
        inline void BOOST_PP_CAT(pstade_pod_constant_check_of_, O)() \
        { \
            pstade::pod_constant_detail::must_be_pod(F()); \
        } \
    /**/

#endif


#if BOOST_WORKAROUND(__GNUC__, >= 4)
    #define PSTADE_POD_CONSTANT_unused __attribute__ ((__unused__))
#else
    #define PSTADE_POD_CONSTANT_unused
#endif


#endif
