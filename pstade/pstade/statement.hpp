#ifndef PSTADE_STATEMENT_HPP
#define PSTADE_STATEMENT_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Strictly speaking, there seems no guarantee that
// the statement is executed before 'main',
// though no compilers can do such delay.


#include <boost/preprocessor/cat.hpp>
#include <boost/serialization/force_include.hpp> // BOOST_DLLEXPORT
#include <pstade/instance.hpp>


#define PSTADE_STATEMENT(Label, Statement) \
    PSTADE_STATEMENT_define_initializer_type(Label, Statement) \
    \
    PSTADE_INSTANCE(PSTADE_STATEMENT_initializer_type(Label), \
        PSTADE_STATEMENT_initializer(Label), value) \
    \
    BOOST_DLLEXPORT \
    PSTADE_STATEMENT_initializer_type(Label) * \
    PSTADE_STATEMENT_function(Label)() \
    { \
        return &PSTADE_STATEMENT_initializer(Label); \
    } \
/**/


#define PSTADE_STATEMENT_define_initializer_type(Label, Statement) \
    struct PSTADE_STATEMENT_initializer_type(Label) \
    { \
        PSTADE_STATEMENT_initializer_type(Label)() \
        { \
            Statement \
        } \
    }; \
/**/


#define PSTADE_STATEMENT_initializer_type(Label) \
    BOOST_PP_CAT(pstade_statement_initializer_type_of_, Label) \
/**/


#define PSTADE_STATEMENT_initializer(Label) \
    BOOST_PP_CAT(pstade_statement_initializer_of_, Label) \
/**/


#define PSTADE_STATEMENT_function(Label) \
    BOOST_PP_CAT(pstade_statement_function_of_, Label) \
/**/


#endif
