
#include <pstade/oven/identity_range.hpp>

#include <pstade/used.hpp>
#include <string>
#include <iostream>

using namespace pstade;

std::string str;


template< class T >
void copy(T x)
{
    pstade::used(x);
}

void test()
{
    oven::identity_range<std::string> src(str);
    ::copy(src);
    ::pstade::used(src);
}


int main()
{
    ::test();
}
