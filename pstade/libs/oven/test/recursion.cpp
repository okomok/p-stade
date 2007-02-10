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
#include <pstade/oven/recursion.hpp>


#include <pstade/oven/reversed.hpp>
#include <pstade/oven/appended.hpp>
#include <pstade/oven/prepended.hpp>
#include <pstade/oven/any_range.hpp>
#include <pstade/oven/taken.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/shared.hpp>
#include <pstade/oven/jointed.hpp>
#include <pstade/oven/as_single.hpp>


namespace oven = pstade::oven;
using namespace pstade::oven;


typedef
    any_range<int const&, boost::forward_traversal_tag>
range;


range make_ones()
{
    range *pones = new range();

    *pones = new int const(1)|as_shared_single|jointed(recursion(*pones));

    return pones|shared;
}


void test()
{
    {
        range ones;

        int const one = 1;
        ones = recursion(ones)|prepended(one);

        int const ans_[] = { 1,1,1,1,1,1,1,1 };
        std::vector<int> ans = ans_|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            ones|taken(8),
            ans
        ) );
    }
    { // reverse
        any_range<int const&, boost::bidirectional_traversal_tag> ones;

        int const one = 1;
        ones = recursion(ones)|appended(one);

        int const ans_[] = { 1,1,1,1,1,1,1,1 };
        std::vector<int> ans = ans_|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            ones|reversed|taken(8),
            ans
        ) );
    }
    {
        int const ans_[] = { 1,1,1,1,1,1,1,1 };
        std::vector<int> ans = ans_|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            ::make_ones()|taken(8),
            ans
        ) );
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
