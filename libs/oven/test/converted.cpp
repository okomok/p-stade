#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/converted.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <pstade/egg/is_same.hpp>
#include <pstade/oven/equals.hpp>


namespace oven = pstade::oven;
using namespace oven;


void pstade_minimal_test()
{
    {
        int a[] = { 6,4,2,3,6,3,8,5,1,4,6,8,3,1 };
        int b[] = { 6,4,2,3,6,3,8,5,1,4,6,8,3,1 };
        BOOST_CHECK( equals(a, a|converted<int const&>(), pstade::egg::is_same) );
        test::random_access_constant(op_make_converted<int const&>()(b), a);
        test::random_access_swappable(op_make_converted<int&>()(b), a);
    }
}
