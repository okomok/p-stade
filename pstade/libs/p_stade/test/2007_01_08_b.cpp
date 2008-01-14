#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <boost/mpl/equal.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/template_arguments.hpp>
#include <utility>


namespace mpl = boost::mpl;
using namespace pstade;


BOOST_MPL_ASSERT((mpl::equal<
    mpl::vector<int, double>,
    template_arguments_of< std::pair<int, double> >::type
>));

BOOST_MPL_ASSERT((boost::is_same<
    template_arguments_copy< mpl::list<char, float>, std::pair<int, int> >::type,
    std::pair<char, float>
>));


template<class T>
struct foo
{
    BOOST_MPL_ASSERT((boost::is_integral<T>));
};


#if 0
// is_integral assertion fails.
typedef
    mpl::apply<foo<mpl::_1>, void>::type
error_t;
#endif


typedef
    template_arguments_copy<
        mpl::apply<
            template_arguments_of< foo<mpl::_1> >::type,
            void
        >::type,
        foo<mpl::_1>
    >::type
ok_t;

BOOST_MPL_ASSERT((boost::is_same<foo<void>, ok_t>));



void test()
{
}


int test_main(int, char *[])
{
    ::test();
    return 0; 
} 
