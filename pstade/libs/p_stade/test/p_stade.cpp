#include <pstade/vodka/drink.hpp>


#include <boost/lambda/core.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <pstade/minimal_test.hpp>
#include <boost/function.hpp>
#include <pstade/egg/plus.hpp>

namespace bll = boost::lambda;

int my_plus(int x, int y)
{
    return x+y;
}


void pstade_minimal_test()
{
    int x = 1, y = 10;
    bll::bind(&my_plus, bll::_1, bll::protect(bll::_1 + 2))(x, y);//(y);
//    (bll::_1 + bll::protect(bll::_1 + 2))(x)(y);
}
