#include <pstade/vodka/drink.hpp>


#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/bind.hpp>
#include <pstade/minimal_test.hpp>


namespace bll = boost::lambda;

void pstade_minimal_test()
{
// \x -> (\y -> x + y)

    int i = 1, j = 2;

    BOOST_CHECK(
        bll::bind(
            bll::_1 + bll::_2,
            bll::_1
        )  (i)(j)
        == 3
    );
}
