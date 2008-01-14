#include <pstade/vodka/drink.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>


// PStade.P_Stade;
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/share_range.hpp>
#include <pstade/oven/sort_range.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <boost/foreach.hpp>


using boost::unit_test::test_suite;


template< class Range, class Fun >
Fun for_each_ex(const Range& rng, Fun f)
{
    return std::for_each(boost::begin(rng), boost::end(rng), f);
}

void output(char ch) { std::cout << ch; }


void test()
{
	using namespace pstade;

	std::string str("abc");
    BOOST_FOREACH (char ch, str) {
        std::cout << ch;
    }

	BOOST_FOREACH (char ch, std::string("abc")) {
        std::cout << ch;
    }

    ::for_each_ex(boost::make_iterator_range(std::string("abc")), output);


	BOOST_FOREACH (char ch, boost::make_iterator_range(std::string("abc"))) { // crash!
        std::cout << ch;
    }

    BOOST_FOREACH (char ch, boost::make_iterator_range(new std::string("abc")|oven::shared)) {
        std::cout << ch;
    }

    BOOST_FOREACH (char ch, new std::string("cba")|oven::shared|oven::sorted) {
        std::cout << ch;
    }
}


#define BOOST_LIB_NAME boost_test_exec_monitor
#include <boost/config/auto_link.hpp>


test_suite* init_unit_test_suite(int, char* []) 
{
    test_suite* test = BOOST_TEST_SUITE("now test");
    test->add(BOOST_TEST_CASE(&::test));
    return test;
}
