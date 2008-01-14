#ifndef PSTADE_UNIT_TEST_HPP
#define PSTADE_UNIT_TEST_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>


void pstade_unit_test();


boost::unit_test::test_suite *
init_unit_test_suite(int, char *[])
{
    boost::unit_test::test_suite *test = BOOST_TEST_SUITE("P-Stade Test Suite");
    test->add(BOOST_TEST_CASE(&::pstade_unit_test));
    return test;
}


#endif
