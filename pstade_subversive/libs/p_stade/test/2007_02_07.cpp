#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <boost/detail/function2.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/placeholders.hpp>


template<class X, class Y>
struct foo_base
{
    typedef X& result_type;

    result_type operator()(X& x, Y&) const
    {
        return x;
    }
};

template<class Y>
struct foo_base<std::string, Y>
{
    typedef std::string& result_type;

    result_type operator()(std::string& str, Y&) const
    {
        return str;
    }
};


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) // for Boost v1.33
    struct op_foo :
        boost::detail::function2< foo_base<boost::mpl::_, boost::mpl::_> >
    { };
#else
    typedef
        boost::detail::function2< foo_base<boost::mpl::_, boost::mpl::_> >
    op_foo;
#endif


BOOST_MPL_ASSERT(( boost::is_same<int&, boost::result_of<op_foo(int&, int)>::type> ));
BOOST_MPL_ASSERT(( boost::is_same<int const&, boost::result_of<op_foo(int const&, int)>::type> ));
BOOST_MPL_ASSERT(( boost::is_same<int const&, boost::result_of<op_foo(int, int)>::type> )); // rvalue

BOOST_MPL_ASSERT(( boost::is_same<std::string&, boost::result_of<op_foo(std::string&, int)>::type> ));


void test()
{
    int x = 10;
    int y = 5;
    BOOST_CHECK( op_foo()(x, y) == 10 );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}