#ifndef PSTADE_NONVIRTUAL_HPP
#define PSTADE_NONVIRTUAL_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Suppress a gcc warning for nonvirtual destructor.


#if defined(__GNUC__)
    #define PSTADE_NONVIRTUAL virtual
#else
    #define PSTADE_NONVIRTUAL
#endif


#endif
