
#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

struct A { };
struct B { };

BOOST_STATIC_ASSERT((boost::is_convertible< boost::shared_ptr<A>, boost::shared_ptr<B> >::value));

int main()
{
    boost::shared_ptr<A> pa;
    //boost::shared_ptr<B> pb = pa;
}
