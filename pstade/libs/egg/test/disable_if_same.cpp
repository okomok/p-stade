#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <pstade/egg.hpp>


struct a_baby
{
    template< class Unused, class X, class Y >
    struct result
    {
        typedef void type;
    };

    template< class Result, class X, class Y >
    Result call(X& x, Y& y)
    {
        return x * y;
    }

    template< class T >
    a_baby(T const&)
    {
        BOOST_ASSERT(false);
    }

    template< class T >
    a_baby& operator=(T const&)
    {
        BOOST_ASSERT(false);
        return *this;
    }

    a_baby()
    { }
};


PSTADE_EGG_FUNCTION(a_function, a_baby)


void test()
{
    {
        a_function_fun a;
        a_function_fun b(a);
        b = a;
    }

    {
        a_function_fun const a;
        a_function_fun b(a);
        b = a;
    }

}


void test2()
{
    int volatile y_ = 5;
    int volatile result_ = 4 * y_;

    BOOST_CHECK( result_ == 20);
}


int test_main(int, char*[])
{
    ::test();
    ::test2();
    return 0;
}
