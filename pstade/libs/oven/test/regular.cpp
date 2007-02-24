#include <pstade/vodka/drink.hpp>


#if defined(__MINGW32__)
    #define PSTADE_OVEN_TEST_MINIMAL
#endif

#if !defined(PSTADE_OVEN_TEST_MINIMAL)
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
#include <pstade/oven/regular.hpp>


#include <string>
#include <pstade/functional.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/filtered.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <boost/noncopyable.hpp>
#include <pstade/new_delete.hpp>


template< class F >
void regular_check(F f)
{
    F f1(f);
    F f2;
    f2 = f1;
}


struct not_equal_to_c :
    private boost::noncopyable
{
    typedef bool result_type;

    bool operator()(char ch)
    {
        return ch != 'c';
    }
};


void test()
{
    namespace lambda = boost::lambda;
    namespace oven = pstade::oven;
    using namespace oven;

    {
        ::regular_check(regular(lambda::_1 != 'c'));
        ::regular_check(regular(lambda::_1 += 1));
        ::regular_check(regular_stateless(pstade::op_less()));
        ::regular_check(regular_ref(pstade::less));
    }
    {
        std::string rng("abcABc12c");
        std::vector<char> expected = std::string("abAB12")|copied;

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|filtered(regular(lambda::_1 != 'c')),
            expected
        ) );

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|filtered(regular_stateless(lambda::_1 != 'c')),
            expected
        ) );


        ::not_equal_to_c nonC;
        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|filtered(regular_ref(nonC)),
            expected
        ) );
    }
    {
        BOOST_CHECK( oven::equals(
            std::string("abcdefg")
                | filtered(regular(lambda::_1 != 'c'))
                | filtered(regular(lambda::_1 != 'f')),
            std::string("abdeg")
        ) );
    }
}


#if !defined(PSTADE_OVEN_TEST_MINIMAL)

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
