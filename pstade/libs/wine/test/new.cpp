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


#include <pstade/new.hpp>


#include <boost/smart_ptr.hpp>


struct A0 { A0() { } };
struct A1 { A1(int) { } };
struct A2 { A2(int, int) { } };
struct A3 { A3(int, int, int) { } };
struct A4 { A4(int, int, int, int) { } };
struct A5 { A5(int, int, int, int, int) { } };


void test()
{
    {
        int i0, i1, i2, i3, i4;
        std::auto_ptr<A0> p0(pstade::new_<A0>());
        std::auto_ptr<A1> p1(pstade::new_<A1>( 0));
        std::auto_ptr<A2> p2(pstade::new_<A2>( 0,i1));
        std::auto_ptr<A3> p3(pstade::new_<A3>(i0, 1,i2)); 
        std::auto_ptr<A4> p4(pstade::new_<A4>( 0,i1, 2, 3));
        std::auto_ptr<A5> p5(pstade::new_<A5>( 0, 1, 2,i3,i4));
    }

    {
        std::auto_ptr<A2>     ap(pstade::new_<A2>(0, 1));
        boost::scoped_ptr<A3> cp(pstade::new_<A3>(0, 1, 2));
        // boost::shared_ptr<A4> sp(pstade::new_<A4>(0, 1, 2, 3)); // Boost v1.34 -
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

