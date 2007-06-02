
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_const.hpp>

using namespace boost;


BOOST_MPL_ASSERT_NOT((
    is_const<iterator_value<boost::ptr_vector<int>::const_iterator>::type>
));

int main()
{
}
