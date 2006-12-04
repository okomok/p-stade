#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <pstade/egg/function.hpp>


struct baby_state_fun
{
    template< class Myself, class X >
    struct apply
    {
        typedef void type;
    };

    template< class Result, class X >
    void call(X& x)
    {
        m_state = x;
    }

    int m_state;
};


using namespace pstade;


egg::function< baby_state_fun > g_fun;


void test()
{
    {
        g_fun(3);
        BOOST_CHECK( g_fun.m_state == 3 );
        g_fun(5);
        BOOST_CHECK( g_fun.m_state == 5 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
