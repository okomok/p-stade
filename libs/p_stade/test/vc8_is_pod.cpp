
#include <boost/type_traits/is_pod.hpp>
#include <boost/static_assert.hpp>


struct E {};

template<class T>
struct A {};

template<>
struct A<int> : E
{};

BOOST_STATIC_ASSERT((boost::is_pod<A<double> >::value));
BOOST_STATIC_ASSERT((!boost::is_pod<A<int> >::value));


struct B
{
    A<double> a;
};
BOOST_STATIC_ASSERT((boost::is_pod<B>::value)); 


struct C
{
    A<int> a;
};
BOOST_STATIC_ASSERT((boost::is_pod<C>::value)); // !?


int main() {}
