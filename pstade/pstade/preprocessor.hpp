#ifndef PSTADE_PREPROCESSOR_HPP
#define PSTADE_PREPROCESSOR_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>


// 'BOOST_PP_SEQ_CAT' isn't ugly?
#define PSTADE_PP_CAT3(A0, A1, A2) \
    BOOST_PP_CAT(A0, BOOST_PP_CAT(A1, A2)) \
/**/


#define PSTADE_PP_ENUM_REF_PARAMS(Count, Param) \
    BOOST_PP_ENUM_BINARY_PARAMS(Count, Param, & BOOST_PP_INTERCEPT) \
/**/

#define PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(Count, Param, Arg) \
    BOOST_PP_ENUM_BINARY_PARAMS(Count, Param, & Arg) \
/**/


// If 'Param' is array type, VC++7.1 might break down. Take care.
#define PSTADE_PP_ENUM_CREF_PARAMS(Count, Param) \
    BOOST_PP_ENUM_BINARY_PARAMS(Count, Param, const& BOOST_PP_INTERCEPT) \
/**/

#define PSTADE_PP_ENUM_CREF_PARAMS_WITH_OBJECTS(Count, Param, Arg) \
    BOOST_PP_ENUM_BINARY_PARAMS(Count, Param, const& Arg) \
/**/


#endif
