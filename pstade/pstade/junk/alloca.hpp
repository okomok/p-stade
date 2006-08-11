#ifndef PSTADE_ALLOCA_HPP
#define PSTADE_ALLOCA_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_MSVC
#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/scoped_array.hpp>
#include <boost/type_traits/is_pod.hpp>


#if !defined(PSTADE_ALLOCA_THRESHOLD_BYTES)
    #define PSTADE_ALLOCA_THRESHOLD_BYTES 1024 // follows '_malloca'.
#endif


#if !defined(PSTADE_ALLOCA_INTRINSIC_ALLOCA)

    #if defined(BOOST_MSVC)
        #include <malloc.h> // _alloca
        #define PSTADE_ALLOCA_INTRINSIC_ALLOCA _alloca
    #else
        #error 'PSTADE_ALLOCA_INTRINSIC_ALLOCA' must be defined.
    #endif

#endif


#define PSTADE_ALLOCA(Type, Var, Size) \
    PSTADE_ALLOCA_assert(Type) \
    \
    boost::scoped_array<Type> PSTADE_ALLOCA_scoped(Var); \
    Type *Var; \
    if (PSTADE_ALLOCA_THRESHOLD_BYTES < Size) { \
        PSTADE_ALLOCA_scoped(Var).reset(new Type[Size]); \
        Var = PSTADE_ALLOCA_scoped(Var).get(); \
    } \
    else { \
        Var = static_cast<Type *>( PSTADE_ALLOCA_INTRINSIC_ALLOCA(Size) ); \
    } \
/**/


    #define PSTADE_ALLOCA_scoped(Var) \
        BOOST_PP_CAT(pstade_alloca_scoped_, Var) \
    /**/


    #define PSTADE_ALLOCA_assert(Type) \
        BOOST_MPL_ASSERT((boost::is_POD<Type>)); \
    /**/


#endif
