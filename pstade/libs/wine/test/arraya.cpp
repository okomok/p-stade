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


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/arraya.hpp>


void test()
{
    using namespace pstade;

    arraya<std::string> arr0(40);
    arr0[39] = "abc";
    arraya<std::string> const arr1(400);
    arr1[399] = "cde";
    arraya<std::string, 0> arr2(10);
    arr2[9] = "fgh";
}


#if !defined(PSTADE_WINE_TEST_MINIMAL)

    #include <boost/test/unit_test.hpp>
    using boost::unit_test::test_suite;

    test_suite *
    init_unit_test_suite(int argc, char *argv[])
    {
        test_suite *test = BOOST_TEST_SUITE("Oven Test Suite");
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
