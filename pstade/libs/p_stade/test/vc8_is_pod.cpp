
#include <boost/type_traits/is_pod.hpp>
#include <boost/static_assert.hpp>


struct E {};

struct B : E
{};

struct C
{
    B b;
};
BOOST_STATIC_ASSERT((boost::is_pod<C>::value)); // !?


int main() {}
