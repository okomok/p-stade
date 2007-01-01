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
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/new.hpp>


#include <boost/smart_ptr.hpp>
#include <pstade/automatic.hpp>


struct A0 { A0() { } };
struct A1 { explicit A1(int) { } };
struct A2 { A2(int, int&) { } };
struct A3 { A3(int&, int, int&) { } };
struct A4 { A4(int, int&, int, int) { } };
struct A5 { A5(int, int&, int&, int&, int) { } };


struct S { S(char const*, int, char const*) { } };

template< class T >
void foo(std::auto_ptr<T>, std::auto_ptr<T>)
{ }


struct B { };
struct D : B { };


//PSTADE_AUTOMATIC(happy_new, (op_new_auto<_1>))

struct op_happy_new
{
    
    // hmm,
    // VC++ moving sequence must be in the same scope.
    template<class Y>
    operator std::auto_ptr_ref<Y>() const
    {
        std::auto_ptr<Y> p(new int(3));
        std::auto_ptr_ref<Y> ref(p);
        p.release();
        return ref;
    }
    
    /*
    // needs temporary, then cannot bind to non-const-reference auto_ptr
    template<class To>
    operator To() const
    {
        return To(new int(3));
    }
    */
};

op_happy_new const happy_new = { };


void happy_test()
{
#if 0
    std::auto_ptr<int> p(happy_new);
    BOOST_CHECK( *p == 3 );
#endif
}


void test()
{
    int i = 12;
    int const c = 13;

    using namespace pstade;

    {
        int *p = op_new_<int>()();
        BOOST_CHECK( *p == 0 );
        delete p;
    }
    {
        int *p = op_new_<int>()(3);
        BOOST_CHECK( *p == 3 );
        delete p;
    }
#if 0
    {
        int *p = new_ptr();
        BOOST_CHECK( *p == 0 );
        delete p;
    }
    {
        int *p = new_ptr(3);
        BOOST_CHECK( *p == 3 );
        delete p;
    }
#endif
    {
        std::auto_ptr<A0> p0( (op_new_auto<A0>())() ); // vexing parse.
        //std::auto_ptr<A0> p0_( op_new_auto<A0>().call() );
        *op_new_auto<A0>()();
    }
    {
        std::auto_ptr<A1> p1(op_new_auto<A1>()(i));
        std::auto_ptr<A1> p2(op_new_auto<A1>()(c));
        *op_new_auto<A1>()(c);
    }
    {
        std::auto_ptr<A2> p1(op_new_auto<A2>()(i,i));
        std::auto_ptr<A2> p2(op_new_auto<A2>()(i,i));
        std::auto_ptr<A2> p3(op_new_auto<A2>()(c,i));
    }
    {
        std::auto_ptr<A3> p2(op_new_auto<A3>()(i,c,i));
        std::auto_ptr<A3> p1(op_new_auto<A3>()(i,i,i));
    }
    {
        std::auto_ptr<A4> p1(op_new_auto<A4>()(c,i,c,c));
        std::auto_ptr<A4> p2(op_new_auto<A4>()(c,i,i,c));
        std::auto_ptr<A4> p3(op_new_auto<A4>()(c,i,c,i));
    }
    {
        std::auto_ptr<A5> p1(op_new_auto<A5>()(c,i,i,i,c));
        std::auto_ptr<A5> p2(op_new_auto<A5>()(i,i,i,i,c));
        std::auto_ptr<A5> p3(op_new_auto<A5>()(c,i,i,i,i));
        std::auto_ptr<A5> p4(op_new_auto<A5>()(i,i,i,i,i));
    }
    {
        std::auto_ptr<A2> ap(op_new_auto<A2>()(i,i));
        boost::scoped_ptr<A3> cp(op_new_auto<A3>()(i,i,i));
        // boost::shared_ptr<A4> sp(op_new_auto<A4>()(i,i,i,i)); // Boost v1.34 -
    }
    {
        boost::shared_ptr<A5> p1(op_new_shared<A5>()(c,i,i,i,c));
    }
    {
        ::foo(
            op_new_auto<S>()("exception", i, "safe!"),
            op_new_auto<S>()("exception", i, "safe!")
        );
    }

    {
        std::auto_ptr< ::D > apD(new ::D());
        std::auto_ptr< ::B > apB(apD);

    #if !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        // eternal recursive calls, funny VC++7.1
        std::auto_ptr< ::B > apB_((op_new_auto< ::D >())()); // runtime failure under VC++7.1
    #endif
    }

#if 0
    {
        std::auto_ptr<A4> p1(pstade::new_(c,i,c,c));
    }
#endif
    {
        happy_test();
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

