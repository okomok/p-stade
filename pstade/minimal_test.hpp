#ifndef PSTADE_MINIMAL_TEST_HPP
#define PSTADE_MINIMAL_TEST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/test/minimal.hpp>


void pstade_minimal_test();


int test_main(int, char*[])
{
    ::pstade_minimal_test();
    return 0;
}


#endif
