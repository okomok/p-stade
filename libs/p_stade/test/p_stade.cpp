

#include <boost/lambda/core.hpp>
#include <boost/range/begin.hpp>


template<class A>
struct wrap;

template<class T, std::size_t N>
struct wrap<T[N]>
{
    typedef int type;
};


// doesn't compile.
template<class A>
typename wrap<A const>::type
foo(A const&)
{
    return 0;
}


// compiles.
template<class A>
void
foo_(A const&)
{
    typename wrap<A const>::type x = 0;
    (void)x;
}


int main()
{
    int a[] = { 1, 2 };
    ::foo(a);
//    ::foo_(a);
}
