#include <boost/test/minimal.hpp>


#if !defined(NULLPTR)
    #define NULLPTR 0
#endif


void test()
{
    int *pi = 0;
    BOOST_CHECK(pi == NULLPTR);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
