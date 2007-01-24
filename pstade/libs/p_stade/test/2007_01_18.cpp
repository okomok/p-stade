#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>

#define PSTADE_CONCEPT_CHECK
#include <iostream>
#include <pstade/lambda_result_of.hpp>
#include <pstade/oven.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>


namespace oven = pstade::oven;
using namespace oven;
namespace assign = boost::assign;
namespace lambda = boost::lambda;

void test()
{
    copy(assign::list_of(4)(2)(3)|transformed(lambda::_1 + 1)|regularized|sorted,
        oven::to_ostream<int>(std::cout, "\n"));
}


int test_main(int, char *[])
{
    ::test();
    return 0; 
} 
