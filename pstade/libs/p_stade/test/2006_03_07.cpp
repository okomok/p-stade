#include <boost/test/minimal.hpp>


template< class Ex, class T >
void foo(T&) { }

template< class Ex, class T >
void foo(const T&) { }


void test_2006_03_07()
{
    const int x = 0;
    foo<char, int>(x);
    foo<char, const int>(x);
}


int test_main(int, char*[])
{
    test_2006_03_07();
    return 0;
}
