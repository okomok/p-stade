
#include <cstddef>
#include <pstade/boost_workaround.hpp>
#include <boost/static_assert.hpp>
#include <pstade/egg/detail/array_resurrect.hpp>


template<class A>
struct spec;

template<class T, std::size_t N>
struct spec< T[N] >
{
    BOOST_STATIC_ASSERT(N == 3);
    typedef T* type;
};

template<class A>
struct indirection :
    spec<PSTADE_EGG_ARRAY_RESURRECT(A)>
{};

template<class A>
typename indirection<A const>::type foo(A const& a)
{
    return 0;
};


int main()
{
    int a[3];
    int const *x = ::foo(a);
}
