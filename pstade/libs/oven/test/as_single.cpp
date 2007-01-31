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


#include <pstade/oven/tests.hpp>
#include <pstade/oven/as_single.hpp>


#include <memory>
#include <string>
#include <vector>
#include <pstade/oven/functions.hpp>
#include <pstade/new_delete.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string ans("a");

    {
        BOOST_CHECK( oven::equals('a'|as_single, ans) );
    }
    {
        BOOST_CHECK( oven::equals(as_single('a'), ans) );
    }
    {
        char ch = 'a';
        BOOST_CHECK( oven::equals(oven::as_single(ch), ans) );
    }

    {
        BOOST_CHECK( oven::equals(new char('a')|as_shared_single, ans) );
    }

    {
        BOOST_CHECK( oven::equals(as_shared_single(pstade::op_new_auto<char>()('a')), ans) );
        BOOST_CHECK( oven::equals(pstade::op_new_auto<char>()('a')|as_shared_single, ans) );
    }
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
