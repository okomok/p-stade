
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

BOOST_STATIC_ASSERT((boost::is_same<boost::ptr_vector<int const>::iterator::value_type, int const>::value));

int main() {}
