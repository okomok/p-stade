#ifndef PSTADE_INSTANCE_HPP
#define PSTADE_INSTANCE_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/sequence/detail/instance.hpp>
//
// Copyright David Abrahams 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// The ODR violation buster.


// Usage:
//
// PSTADE_INSTANCE(int, i, value) // value-initialize
// PSTADE_INSTANCE(string, s, ("hello"))


// Reason why 'ValueOrArgSeq' is checked:
//
// Assume you typo 'PSTADE_INSTANCE(bool, b, true)'
// instead of 'PSTADE_INSTANCE(bool, b, (true))'.
// 'b' is value-initialized, thus 'b' becomes 'false'.


#include <boost/config.hpp> // BOOST_MSVC
#include <boost/mpl/aux_/preprocessor/is_seq.hpp>
#include <boost/mpl/aux_/preprocessor/token_equal.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/debug/assert.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/utility/value_init.hpp> // value_initialized


#define PSTADE_INSTANCE(Type, Name, ValueOrArgSeq) \
    BOOST_PP_ASSERT(PSTADE_INSTANCE_is_valid(ValueOrArgSeq)) \
    BOOST_PP_IIF (BOOST_MPL_PP_IS_SEQ(ValueOrArgSeq), \
        PSTADE_INSTANCE_args, \
        PSTADE_INSTANCE_no_args \
    )(Type, Name, ValueOrArgSeq) \
/**/


    #define PSTADE_INSTANCE_is_valid(ValueOrArgSeq) \
        BOOST_PP_IIF (BOOST_MPL_PP_IS_SEQ(ValueOrArgSeq), \
            1 BOOST_PP_TUPLE_EAT(2), \
            BOOST_MPL_PP_TOKEN_EQUAL \
        )(ValueOrArgSeq, value) \
    /**/


    #if !defined(BOOST_MPL_PP_TOKEN_EQUAL_value)
        #define BOOST_MPL_PP_TOKEN_EQUAL_value(A) \
            A \
        /**/
    #endif


    #define PSTADE_INSTANCE_no_args(Type, Name, _) \
        PSTADE_INSTANCE_define_box(Type, Name, PSTADE_INSTANCE_define_v(Type)) \
        namespace { \
            PSTADE_INSTANCE_static \
            Type& Name = PSTADE_INSTANCE_OF(Name); \
        } \
    /**/


    #define PSTADE_INSTANCE_args(Type, Name, ArgSeq) \
        PSTADE_INSTANCE_define_box(Type, Name, PSTADE_INSTANCE_define_a(Type, ArgSeq)) \
        namespace { \
            PSTADE_INSTANCE_static \
            Type& Name = PSTADE_INSTANCE_OF(Name); \
        } \
    /**/


    #define PSTADE_INSTANCE_box_name(Name) \
        BOOST_PP_CAT(pstade_instance_of_, Name) \
    /**/


    #define PSTADE_INSTANCE_define_box(Type, Name, DefineInstance) \
        inline \
        Type& PSTADE_INSTANCE_box_name(Name)() \
        { \
            static DefineInstance \
            return instance; \
        } \
    /**/


// Workaround:
// GCC dynamic initialization sometimes needs the function call syntax.
#define PSTADE_INSTANCE_OF(Name) \
    PSTADE_INSTANCE_box_name(Name)() \
/**/


    #define PSTADE_INSTANCE_define_v(Type) \
        boost::value_initialized< Type > instance; \
    /**/


    #define PSTADE_INSTANCE_define_a(Type, ArgSeq) \
        Type instance(BOOST_PP_SEQ_ENUM(ArgSeq)); \
    /**/


    // Workaround:
    // The weird 'stdafx.h' needs 'static'.
    #if !defined(BOOST_MSVC)
        #define PSTADE_INSTANCE_static
    #else
        #define PSTADE_INSTANCE_static static
    #endif


#endif
