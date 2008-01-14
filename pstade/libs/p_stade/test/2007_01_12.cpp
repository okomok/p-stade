#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


template<class T>
struct x { };

template<class T>
struct y { };

#define MACRO_X(A) X<A>

MACRO_X(::y<int>) a;


void test()
{
}


int test_main(int, char *[])
{
    ::test();
    return 0; 
} 
