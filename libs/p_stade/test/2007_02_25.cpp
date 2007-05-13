#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/type_traits/is_stateless.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/function.hpp>
#include <pstade/oven/regular.hpp>
#include <pstade/used.hpp>
#include <boost/timer.hpp>
#include <string>
#include <vector>


namespace lambda = boost::lambda;
namespace oven = pstade::oven;


struct dummy { };

// large object
struct my_fun :dummy
{
    typedef int result_type;
    int operator()(int i) const
    {
        return i + 1;
    }

#if 0
    std::string s;
    int i;
    double d;
    std::vector<char> v;
#endif
};


template< class F >
void copy(F f)
{
    F f1 = f;
    F f2 = f;
    F f3 = f;
    pstade::used(f1);
    pstade::used(f2);
    pstade::used(f3);
}


void test()
{
    {
        // heap allocation
        boost::function<int(int)> f = lambda::_1 + 1;
        BOOST_CHECK( f(10) == 11 );

        boost::timer t;
        {
            for (int i = 0; i < 1000000; ++i)
                ::copy(f);
        }
        std::cout << t.elapsed();
    }
    std::cout << std::endl;
    {
        // small object optimization
        boost::function<int(int)> f = oven::regular_c(lambda::_1 + 1);
        BOOST_CHECK( f(10) == 11 );

        boost::timer t;
        {
            for (int i = 0; i < 1000000; ++i)
                ::copy(f);
        }
        std::cout << t.elapsed();
    }
}


int test_main(int, char *[])
{
    ::test();
    return 0; 
} 
