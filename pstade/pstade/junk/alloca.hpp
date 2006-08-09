#ifndef PSTADE_ALLOCA_HPP
#define PSTADE_ALLOCA_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <pstade/scoped_memory.hpp>


#if !defined(PSTADE_ALLOCA_INTRINSIC_ALLOCA)

    #if defined(BOOST_MSVC)
        #include <malloc.h>
        #define PSTADE_ALLOCA_INTRINSIC_ALLOCA _alloca
    #endif

#endif


#if !defined(PSTADE_ALLOCA_THRESHOLD_SIZE)
    #define PSTADE_ALLOCA_THRESHOLD_SIZE 128
#endif


#if defined(PSTADE_ALLOCA_INTRINSIC_ALLOCA) \

    #define PSTADE_ALLOCA(Type, Name, Size) \
        pstade::scoped_memory PSTADE_ALLOCA_scoped(Name); \
        Type Name; \
        if (Size < PSTADE_ALLOCA_THRESHOLD_SIZE) { \
            Name = (Type)PSTADE_ALLOCA_INTRINSIC_ALLOCA(Size); \
        } \
        else { \
            PSTADE_ALLOCA_scoped(Name).reset(std::malloc(Size)); \
            Name = PSTADE_ALLOCA_scoped(Name).get_as<Type>(); \
        } \
    /**/

#else

    #define PSTADE_ALLOCA(Type, Name, Size) \
        pstade::scoped_memory PSTADE_ALLOCA_scoped(Name)(std::malloc(Size)); \
        Type Name = PSTADE_ALLOCA_scoped(Name).get_as<Type>(); \
    /**/

#endif


    #define PSTADE_ALLOCA_scoped(Name) \
        BOOST_PP_CAT(pstade_alloca_scoped_, Name) \
    /**/


#endif
