#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./instance_m.hpp"

bool instance_m2_test()
{
    ::g_vector.push_back(g_int);
    return ::g_int == 24 && ::g_char == 'a';
}
