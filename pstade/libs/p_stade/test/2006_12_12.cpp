#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <boost/lambda/core.hpp>
#include <pstade/result_of.hpp>
#include <pstade/forward.hpp>
#include <pstade/as.hpp>
#include <pstade/result_of_lambda.hpp>


using namespace pstade;
namespace lambda = boost::lambda;


void test()
{
    // lambda::_1(12); // error
    lambda::_1(12|to_ref); // ok

    pstade::result_of<
        pstade::result_of<op::forward(op_lambda_1)>::type(int)
    >::type x =
        forward(lambda::_1)(12);

    BOOST_CHECK( x == 12 );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
