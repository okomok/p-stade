#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/boost_begin_end.hpp>
#include <pstade/minimal_test.hpp>


#include <string>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int const a[10] = { 0,1,2,3,4,5,6,7,8,9 };
        BOOST_CHECK( boost_begin(a) == &a[0] );
        BOOST_CHECK( boost_end(a) == &a[10] );
        *boost_begin(a) = 7;
    }
}
