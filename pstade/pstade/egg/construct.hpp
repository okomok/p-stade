#ifndef PSTADE_EGG_CONSTRUCT_HPP
#define PSTADE_EGG_CONSTRUCT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/construct_xxx.hpp"


#define  PSTADE_EGG_CONSTRUCT_RETURN(T, _, Args) \
    return T(Args); \
/**/
#define  PSTADE_EGG_CONSTRUCT_XXX_PARAMS (construct, PSTADE_EGG_CONSTRUCT_RETURN)
#include PSTADE_EGG_CONSTRUCT_XXX() 


#include "./detail/suffix.hpp"
#endif
