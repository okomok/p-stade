#include <boost/lambda/lambda.hpp>
#include <pstade/egg/bll/result_of.hpp>
#include <pstade/oven/removed.hpp>
#include <pstade/oven/regular.hpp>
#include <pstade/oven/equals.hpp>
#include <boost/detail/lightweight_test.hpp>

struct is_negative
{
    typedef bool result_type;
    bool operator()(int x) const
    { return 0 >= x; }
};

int main()
{
    namespace oven = pstade::oven;
    namespace bll = boost::lambda;

    int a[] = { 9,1,3,7,4,31,1,76,9,2,3 };
    int b[] = { -1,0,9,-3,-6,1,3,7,4,31,-2,1,-2,76,-1,9,-6,2,3 };

    BOOST_TEST(oven::equals(a, b | oven::removed(is_negative())));
    BOOST_TEST(oven::equals(a, b | oven::removed(oven::regular(is_negative()))));
    BOOST_TEST(oven::equals(a, b | oven::removed(oven::regular(0 >= bll::_1))));
//  BOOST_TEST(oven::equals(a, b | oven::removed(oven::regular([](int x) { return 0 >= x; }))));

    return boost::report_errors();
}

