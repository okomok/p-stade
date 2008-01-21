#ifndef PSTADE_IGNORE_UNUSED_HPP
#define PSTADE_IGNORE_UNUSED_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if defined(__GNUC__)
    #define PSTADE_IGNORE_UNUSED __attribute__ ((__unused__))
#else
    #define PSTADE_IGNORE_UNUSED
#endif


#endif
