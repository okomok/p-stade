#include <pstade/unit_test.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/arraya.hpp>


void pstade_unit_test()
{
    using namespace pstade;

    arraya<std::string> arr0(40);
    arr0[39] = "abc";
    arraya<std::string> const arr1(400);
    arr1[399] = "cde";
    arraya<std::string, 0> arr2(10);
    arr2[9] = "fgh";
}

