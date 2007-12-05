#ifndef PSTADE_EGG_USE_BRACE_LEVEL0_HPP
#define PSTADE_EGG_USE_BRACE_LEVEL0_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/use_brace.hpp"


namespace pstade { namespace egg {


    struct use_brace_level0
    {
        #define  PSTADE_EGG_DETAIL_USE_BRACE_L {
        #define  PSTADE_EGG_DETAIL_USE_BRACE_R }
        #include PSTADE_EGG_DETAIL_USE_BRACE()
    };


} } // namespace pstade::egg


#endif
