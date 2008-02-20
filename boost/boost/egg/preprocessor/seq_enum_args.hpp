#ifndef BOOST_EGG_PREPROCESSOR_SEQ_ENUM_ARGS_HPP
#define BOOST_EGG_PREPROCESSOR_SEQ_ENUM_ARGS_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/size.hpp>


// (class)(int) -> T0, T1
#define BOOST_EGG_PP_SEQ_ENUM_ARGS(ParamSeq, T) \
    BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(ParamSeq), T) \
/**/


#endif
