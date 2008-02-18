#ifndef BOOST_LIBS_EGG_TEST_EGG_UNIT_TEST_HPP
#define BOOST_LIBS_EGG_TEST_EGG_UNIT_TEST_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>


void egg_unit_test();


boost::unit_test::test_suite *
init_unit_test_suite(int, char *[])
{
    boost::unit_test::test_suite *test = BOOST_TEST_SUITE("Boost.Egg Test Suite");
    test->add(BOOST_TEST_CASE(&egg_unit_test));
    return test;
}


#endif
