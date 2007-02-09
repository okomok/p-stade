#include <pstade/vodka/drink.hpp>


#if defined(__MINGW32__)
    #define PSTADE_WINE_TEST_MINIMAL
#endif

#if !defined(PSTADE_WINE_TEST_MINIMAL)
    #include <boost/test/test_tools.hpp>
    #define BOOST_LIB_NAME boost_test_exec_monitor
    #include <boost/config/auto_link.hpp>
#else
    #include <boost/test/minimal.hpp>
#endif


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_CONCEPT_CHECK
#include <string>
#include <iostream>
#include <pstade/lexical_cast.hpp>
#include <pstade/oven.hpp>
#include <pstade/as.hpp>
#include <pstade/pack.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <pstade/oven/recursion.hpp>


namespace assign = boost::assign;
namespace lambda = boost::lambda;
using namespace pstade::oven;


void test()
{
    {
        any_range<int, boost::single_pass_traversal_tag> fibs;
        int const start[] = { 1, 1 };
        fibs =
            start|transformed(pstade::as_value)|
                jointed(
                    boost::make_tuple(recursion(fibs), recursion(fibs)|dropped(1))|
                        zipped_with(regular(lambda::_1 + lambda::_2))
                )
        ;

        std::cout << (fibs|taken(20));
    }

#if 0
    {
        // dereference is not random access, of course.
        any_range<int, boost::random_access_traversal_tag> fibs;
        int const start[] = { 1, 1 };
        fibs =
            start|transformed(pstade::as_value)|
                jointed(
                    boost::make_tuple(recursion(fibs), recursion(fibs)|dropped(1))|
                        zipped_with(regular(lambda::_1 + lambda::_2))
                )
        ;

        std::cout << (fibs|sliced(0, 2)|taken(20));
    }
#endif 
}


#if !defined(PSTADE_WINE_TEST_MINIMAL)

    #include <boost/test/unit_test.hpp>
    using boost::unit_test::test_suite;

    test_suite *
    init_unit_test_suite(int argc, char *argv[])
    {
        test_suite *test = BOOST_TEST_SUITE("Wine Test Suite");
        test->add(BOOST_TEST_CASE(&::test));

        (void)argc, (void)argv; // unused
        return test;
    }

#else

    int test_main(int, char*[])
    {
        ::test();
        return 0;
    }

#endif
