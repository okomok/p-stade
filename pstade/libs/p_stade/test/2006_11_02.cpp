#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <iostream>
#include <string>
#include <pstade/oven.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <pstade/lambda_result_of.hpp>


namespace oven = pstade::oven;
using namespace oven;
namespace lambda = boost::lambda;


#if 0 
// BUGBUG: every call makes different range.
// even memoized cannot work around.
oven::share_range<std::string> with_delimiter(char ch)
{
    oven::share_range<std::string> rng(
        new std::string(ch + std::string(","))
    );

    return rng;
}
#endif



struct with_delimiter
{
    typedef
        oven::prepend_range<std::string const, char const>
    result_type;
    
    result_type operator()(char const& ch) const
    {
        return result_type(*m_pdelim, ch);
    }

    explicit with_delimiter(std::string const& delim) :
        m_pdelim(&delim)
    { }

    std::string const *m_pdelim;
};


void test()
{
    std::string const delim(",");

    BOOST_CHECK( oven::equals(
        std::string("12345") |
            transformed(::with_delimiter(delim)) |
            concatenated | popped_back,
        std::string("1,2,3,4,5")
    ) );

    BOOST_CHECK( oven::equals(
        std::string("12345") |
            transformed(lambda::bind(make_prepend_range, boost::ref(delim), lambda::_1)) | regularized |
            concatenated | popped_back,
        std::string("1,2,3,4,5")
    ) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
