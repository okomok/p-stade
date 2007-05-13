#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/type_traits/is_stateless.hpp>
#include <boost/mpl/assert.hpp>


template< class F >
void stateless_check(F f)
{
    BOOST_MPL_ASSERT((boost::is_stateless<F>));
}

struct fun
{
    typedef void result_type;
    void operator()(int) const // error without 'const'
    {
    }
};


void test()
{
    boost::lambda::bind(fun(), 4)();
    ::stateless_check( boost::lambda::_1 );
}


int test_main(int, char *[])
{
    ::test();
    return 0; 
} 
