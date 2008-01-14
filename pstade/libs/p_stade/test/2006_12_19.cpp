#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>


template< class T, class Active = void >
struct has_xxx :
    boost::mpl::false_
{ };


template< class T >
struct has_xxx<T, typename T::xxx> :
    boost::mpl::true_
{ };


struct hello
{
    typedef void xxx;
};

struct goodbye
{
};


BOOST_MPL_ASSERT(( ::has_xxx<hello, void> ));
BOOST_MPL_ASSERT_NOT(( ::has_xxx<goodbye, void> ));


int test_main(int, char*[])
{
    return 0;
}
