#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>


struct baby_multiply
{
    template< class Unused, class X, class Y >
    struct result :
        boost::remove_const<X>
    { };


    template< class Result, class X, class Y >
    Result call(X& x, Y& y)
    {
        return x * y;
    }
};


PSTADE_EGG_FUNCTION(multiply, baby_multiply)


void test()
{
    int volatile y = 5;

    boost::result_of< ::multiply_fun(int, int) >::type
        volatile result = ::multiply(4, y);

    BOOST_CHECK( result == 20 );
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
