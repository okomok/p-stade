#include <pstade/vodka/drink.hpp>


#if defined(__MINGW32__)
    #define PSTADE_TEST_MINIMAL
#endif

#if !defined(PSTADE_TEST_MINIMAL)
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
#include <pstade/oven/any_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/ranges.hpp>
#include <pstade/locale.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>


void test()
{
    namespace lambda = boost::lambda;
    namespace oven = pstade::oven;
    using namespace oven;
    using pstade::to_upper;

    {
        std::string rng("8frj91j81hf891y2");
        std::vector<char> expected = rng|copied;

        any_range<char, boost::random_access_traversal_tag> any_(rng);
        any_ = rng;
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            any_,
            expected
        ) );
    }
    {
        std::string str;
        any_range<char, boost::random_access_traversal_tag> any_rng(str|identities);
    }
    {
        std::string rng("hello! any_range!");
        any_range<char const, boost::bidirectional_traversal_tag> any_ =
            rng|transformed(to_upper)|const_lvalues|filtered(lambda::_1 != '!')|regularized;

        BOOST_CHECK( oven::equals(any_, std::string("HELLO ANY_RANGE")) );
    }
}


#if !defined(PSTADE_TEST_MINIMAL)

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
