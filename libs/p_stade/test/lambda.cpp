#include <pstade/vodka/drink.hpp>


#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <pstade/minimal_test.hpp>


namespace bll = boost::lambda;

int main()
{
    int i = 10;
p
// \x -> (\y -> x + y)

    BOOST_CHECK(
        bll::bind(
            bll::_1 + bll::_2,
            bll::_1
        )  (1, 2)
        == 3
    );
}
