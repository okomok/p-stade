#ifndef PSTADE_LIBS_WINE_TEST_INSTANCE_M_HPP
#define PSTADE_LIBS_WINE_TEST_INSTANCE_M_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>


#include <vector>


PSTADE_INSTANCE((int), g_int, (12))
PSTADE_INSTANCE((char) const, g_char, ('a'))
PSTADE_INSTANCE((std::vector<int>), g_vector, value)


#endif
