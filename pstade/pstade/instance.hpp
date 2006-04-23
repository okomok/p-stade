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
// PSTADE_INSTANCE((map<int,int>), m, value)


// Reason why 'ValueOrArgSeq' is strict:
//
// Assume you typo 'PSTADE_INSTANCE(bool, b, true)'
// instead of 'PSTADE_INSTANCE(bool, b, (true))'.
// 'b' is value-initialized, thus 'b' becomes 'false'.


#include <boost/config.hpp>
#include <boost/mpl/aux_/preprocessor/is_seq.hpp>
#include <boost/mpl/aux_/preprocessor/token_equal.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/debug/assert.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/utility/value_init.hpp> // value_initialized
#include <pstade/comma_protect.hpp>


#define PSTADE_INSTANCE(Type, Name, ValueOrArgSeq) \
    BOOST_PP_ASSERT(PSTADE_INSTANCE_valid(ValueOrArgSeq)) \
    \
    BOOST_PP_IIF (BOOST_MPL_PP_IS_SEQ(ValueOrArgSeq), \
        PSTADE_INSTANCE_args, \
        PSTADE_INSTANCE_no_args \
    )(Type, Name, ValueOrArgSeq) \
/**/


    #define PSTADE_INSTANCE_valid(ValueOrArgSeq) \
        BOOST_PP_IIF (BOOST_MPL_PP_IS_SEQ(ValueOrArgSeq), \
            1 BOOST_PP_TUPLE_EAT(2), \
            BOOST_MPL_PP_TOKEN_EQUAL \
        )(ValueOrArgSeq, value) \
    /**/


    #define BOOST_MPL_PP_TOKEN_EQUAL_value(A) \
        A \
    /**/


    #define PSTADE_INSTANCE_no_args(Type, Name, Unused) \
        PSTADE_INSTANCE_define_fun(Type, Name, PSTADE_INSTANCE_define_x_v(Type)) \
        \
        namespace { \
            PSTADE_INSTANCE_static \
            PSTADE_INSTANCE_comma_protect(Type)& Name = PSTADE_INSTANCE_call_fun(Name); \
        } \
    /**/


    #define PSTADE_INSTANCE_args(Type, Name, ArgSeq) \
        PSTADE_INSTANCE_define_fun(Type, Name, PSTADE_INSTANCE_define_x_a(Type, ArgSeq)) \
        \
        namespace { \
            PSTADE_INSTANCE_static \
            PSTADE_INSTANCE_comma_protect(Type)& Name = PSTADE_INSTANCE_call_fun(Name); \
        } \
    /**/


    #define PSTADE_INSTANCE_define_fun(Type, Name, DefineX) \
        inline \
        PSTADE_INSTANCE_comma_protect(Type)& BOOST_PP_CAT(pstade_instance_of_, Name)() \
        { \
            static DefineX \
            return x; \
        } \
    /**/


    #define PSTADE_INSTANCE_call_fun(Name) \
        BOOST_PP_CAT(pstade_instance_of_, Name)() \
    /**/


    #define PSTADE_INSTANCE_define_x_v(Type) \
        boost::value_initialized< PSTADE_INSTANCE_comma_protect(Type) > x; \
    /**/


    #define PSTADE_INSTANCE_define_x_a(Type, ArgSeq) \
        PSTADE_INSTANCE_comma_protect(Type) x(BOOST_PP_SEQ_ENUM(ArgSeq)); \
    /**/


    #define PSTADE_INSTANCE_comma_protect(Type) \
        pstade::comma_protect<void(Type)>::type \
    /**/


    // Workaround:
    //   The weird 'stdafx.h' needs 'static'.
    //
    #if !defined(BOOST_MSVC)
        #define PSTADE_INSTANCE_static
    #else
        #define PSTADE_INSTANCE_static static
    #endif


#endif
