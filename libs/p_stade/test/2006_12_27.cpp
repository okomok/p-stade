#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <string>


namespace abc {
    template< class T >
    void bar();
}


template< class T >
void foo(T x) 
{
    abc::bar(std::string(), x);
}


void test()
{
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
