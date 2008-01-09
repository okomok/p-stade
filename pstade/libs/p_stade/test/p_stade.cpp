
#include <cstddef>
#include <pstade/boost_workaround.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/assert.hpp>


template<class A>
struct klass;

template<class T, std::size_t N>
struct klass< T[N] >
{
    BOOST_STATIC_ASSERT(N == 3);
    typedef T* type;
};


template<class A, class B = void(A)>
struct klass2 :
    klass<A>
{};

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
template<class A, class T, std::size_t N>
struct klass2<A, void(T[N]) > :
    klass<T [N] >
{};
#endif

template<class A>
typename klass2<A const>::type foo(A const& a)
{
    return 0;
};


int main()
{
    int a[3];
    int *x = ::foo(a);
}
