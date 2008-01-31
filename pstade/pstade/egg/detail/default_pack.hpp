#ifndef PSTADE_EGG_DETAIL_DEFAULT_PACK_HPP
#define PSTADE_EGG_DETAIL_DEFAULT_PACK_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../config.hpp" // PSTADE_EGG_HAS_FUSIONS


#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include "../fusion/pack.hpp"
    #define PSTADE_EGG_DEFAULT_PACK pstade::egg::X_fusion_pack
#else
    #include "../tuple_pack.hpp"
    #define PSTADE_EGG_DEFAULT_PACK pstade::egg::X_tuple_pack
#endif


#endif
