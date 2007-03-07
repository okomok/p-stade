
#include <boost/utility/result_of.hpp>


int my_fun(int) { return 0; }


template< class F >
void test(F )
{
    typedef typename
        boost::result_of<F()>::type
    result_t; // shall be 'void'.
}


int main()
{
    ::test(&my_fun);
}
