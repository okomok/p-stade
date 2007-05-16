#include <boost/test/minimal.hpp>

#include <boost/lambda/core.hpp> // make_const


// See: <boost/spirit/phoenix/function/detail/function_eval.hpp>
//
template< class T>
T& help_rvalue_deduction(T& x)
{
    return x;
}

template< class T >
const T& help_rvalue_deduction(const T& x)
{
    return x;
}


template< class T >
void foo(T& x)
{ }


template< class T >
bool bar(T& x)
{
    return (x = 2); // typo!
}


void test_2006_03_03()
{
    using namespace boost;


    int x;
    ::foo(lambda::make_const(1));
    // ::bar(lambda::make_const(x)); // error

    ::foo(::help_rvalue_deduction(x));
    ::foo(::help_rvalue_deduction(1));
}


int test_main(int, char*[])
{
    test_2006_03_03();
    return 0;
}
