#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <boost/lambda/core.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <pstade/egg/function.hpp>


struct baby_multiply
{
    template< class Myself, class X, class Y >
    struct apply :
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
    namespace lambda = boost::lambda;

    {
        int x = 10, y = 20;
        int result = lambda::bind(multiply, lambda::_1, lambda::_2)(x, y);
        BOOST_CHECK(result == 200);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
