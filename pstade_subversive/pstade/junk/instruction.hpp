#ifndef PSTADE_INSTRUCTION_HPP
#define PSTADE_INSTRUCTION_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/serialization/force_include.hpp> // BOOST_DLLEXPORT


#define PSTADE_INSTRUCTION(Label, Instruction) \
    PSTADE_INSTRUCTION_define_initializer_type(Label, Instruction) \
    \
    PSTADE_INSTANCE(PSTADE_INSTRUCTION_initializer_type(Label), \
	    PSTADE_INSTRUCTION_initializer(Label), value) \
    \
    BOOST_DLLEXPORT \
    PSTADE_INSTRUCTION_initializer_type(Label) * \
    PSTADE_INSTRUCTION_function(Label)() \
    { \
        return &PSTADE_INSTRUCTION_initializer(Label); \
    } \
/**/


#define PSTADE_INSTRUCTION_define_initializer_type(Label, Instruction) \
    struct PSTADE_INSTRUCTION_initializer_type(Label) \
    { \
        PSTADE_INSTRUCTION_initializer_type(Label)() \
        { \
            Instruction \
        } \
    }; \
/**/


#define PSTADE_INSTRUCTION_initializer_type(Label) \
    BOOST_PP_CAT(pstade_instruction_initializer_type_of_, Label) \
/**/


#define PSTADE_INSTRUCTION_initializer(Label) \
    BOOST_PP_CAT(pstade_instruction_initializer_of_, Label) \
/**/


#define PSTADE_INSTRUCTION_function(Label) \
    BOOST_PP_CAT(pstade_instruction_function_of_, Label) \
/**/


#endif
