#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <boost/utility/result_of.hpp>
#include <pstade/pipable.hpp>


int increment(int i)
{
    return i + 1;
}

int decrement(int i)
{
    return i - 1;
}

int multiply(int i, int j)
{
    return i * j;
}


using namespace pstade;


typedef
    pipable_fun
typeof_pipable;


boost::result_of<typeof_pipable(int (*)(int))>::type incremented =
    pipable(&increment);

boost::result_of<typeof_pipable(int (*)(int))>::type decremented =
    pipable(&decrement);

boost::result_of<typeof_pipable(int (*)(int, int))>::type multiplied =
    pipable(&multiply);


void test()
{
    BOOST_CHECK( 7 == decrement(multiply(increment(3), 2)) );
    BOOST_CHECK( 7 == ( 3|pipable(&increment)|pipable(&multiply)(2)|pipable(&decrement) ) );
    BOOST_CHECK( 7 == ( 3|incremented|multiplied(2)|decremented ) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
