#ifndef PSTADE_EGG_DETAIL_CONFIG_HPP
#define PSTADE_EGG_DETAIL_CONFIG_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>


#if !defined(PSTADE_EGG_MAX_ARITY)
    #define PSTADE_EGG_MAX_ARITY 5
#endif


#define PSTADE_EGG_PIPABLE_MAX_ARITY \
    BOOST_PP_DEC(PSTADE_EGG_MAX_ARITY) \
/**/


#endif
