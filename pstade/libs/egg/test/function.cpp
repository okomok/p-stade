#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>

#include <string>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/mpl/assert.hpp>


#include <pstade/egg/function.hpp>


struct foo_impl
{
    template< class Unused, class Arg0, class Arg1 = void >
    struct result
    {
        typedef Arg0 type;
    };

    template< class Result, class Arg0 >
    Result call(Arg0& a0)
    {
        return a0 * a0;
    }

    template< class Result, class Arg0, class Arg1 >
    Result call(Arg0& a0, Arg1& a1)
    {
        return a0 * a1;
    }
};


struct bar_impl
{
    typedef int
    nullary_result_type;

    template< class Result >
    Result call()
    {
        return 1;
    }
};


struct hoge_impl
{
    typedef std::string
    nullary_result_type;

    template< class Unused, class Arg0, class Arg1 = void >
    struct result
    {
        typedef Arg0 type;
    };

    template< class Result >
    Result call()
    {
        return "hello";
    }

    template< class Result, class Arg0 >
    Result call(Arg0& a0)
    {
        return a0 + a0;
    }

    template< class Result, class Arg0, class Arg1 >
    Result call(Arg0& a0, Arg1& a1)
    {
        return a0 + a1;
    }
};


struct qoo_impl
{
    qoo_impl(int, double) { }

    template< class Unused, class Arg0, class Arg1 >
    struct result
    {
        typedef Arg0 type;
    };

    template< class Result, class Arg0, class Arg1 >
    Result call(Arg0& a0, Arg1& a1)
    {
        return a0 * a1;
    }
};

typedef pstade::egg::function<qoo_impl> qoo_fun;

PSTADE_EGG_FUNCTION(foo, foo_impl)
PSTADE_EGG_FUNCTION(bar, bar_impl)
PSTADE_EGG_FUNCTION(hoge, hoge_impl)


BOOST_MPL_ASSERT_NOT(( pstade::egg::baby_result_detail::has_nullary_result_type<foo_impl> ));
BOOST_MPL_ASSERT(( pstade::egg::baby_result_detail::has_nullary_result_type<bar_impl> ));
BOOST_MPL_ASSERT(( pstade::egg::baby_result_detail::has_nullary_result_type<hoge_impl> ));


BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<foo_fun(int)>::type, int> ));
BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<foo_fun(int&)>::type, int> ));
BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<foo_fun(int, int)>::type, int> ));
BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<foo_fun(int&, int)>::type, int> ));

BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<bar_fun()>::type, int> ));

BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<hoge_fun()>::type, std::string> ));
BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<hoge_fun(int&)>::type, int> ));
BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<hoge_fun(int, int)>::type, int> ));
BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<hoge_fun(int&, int)>::type, int> ));


void test_fun()
{
    BOOST_CHECK( bar() == 1 );

    BOOST_CHECK( foo(3) == 3*3 );
    BOOST_CHECK( foo(2, 3) == 2*3 );

    BOOST_CHECK( hoge() == "hello" );
    BOOST_CHECK( hoge(4) == 4+4 );
    BOOST_CHECK( hoge(5, 6) == 5+6 );

    qoo_fun(1,2)(3,4);
}


int test_main(int, char*[])
{
    test_fun();
    return 0;
}
