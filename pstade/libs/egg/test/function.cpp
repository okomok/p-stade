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
    struct apply
    {
        typedef Arg0 type;
    };

    template< class Result, class Arg0 >
    Result call(Arg0& a0) const
    {
        return a0 * a0;
    }

    template< class Result, class Arg0, class Arg1 >
    Result call(Arg0& a0, Arg1& a1) const
    {
        return a0 * a1;
    }
};


struct bar_impl
{
    typedef int
    nullary_result_type;

    template< class Result >
    Result call() const
    {
        return 1;
    }
};


struct hoge_impl
{
    typedef std::string
    nullary_result_type;

    template< class Unused, class Arg0, class Arg1 = void >
    struct apply
    {
        typedef Arg0 type;
    };

    template< class Result >
    Result call() const
    {
        return "hello";
    }

    template< class Result, class Arg0 >
    Result call(Arg0& a0) const
    {
        return a0 + a0;
    }

    template< class Result, class Arg0, class Arg1 >
    Result call(Arg0& a0, Arg1& a1) const
    {
        return a0 + a1;
    }
};


struct qoo_impl
{
    qoo_impl(int, double) { }

    template< class Unused, class Arg0, class Arg1 >
    struct apply
    {
        typedef Arg0 type;
    };

    template< class Result, class Arg0, class Arg1 >
    Result call(Arg0& a0, Arg1& a1) const
    {
        return a0 * a1;
    }

    void hello() const
    { }
};

typedef pstade::egg::function<qoo_impl> op_qoo;

PSTADE_EGG_FUNCTION(foo, foo_impl)
PSTADE_EGG_FUNCTION(bar, bar_impl)
PSTADE_EGG_FUNCTION(hoge, hoge_impl)


BOOST_MPL_ASSERT_NOT(( pstade::egg::baby_result_detail::has_nullary_result_type<foo_impl> ));
BOOST_MPL_ASSERT(( pstade::egg::baby_result_detail::has_nullary_result_type<bar_impl> ));
BOOST_MPL_ASSERT(( pstade::egg::baby_result_detail::has_nullary_result_type<hoge_impl> ));


BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<op_foo(int)>::type, int const> ));
BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<op_foo(int&)>::type, int> ));
BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<op_foo(int, int)>::type, int const> ));
BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<op_foo(int&, int)>::type, int> ));

BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<op_bar()>::type, int> ));

BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<op_hage()>::type, std::string> ));
BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<op_hage(int&)>::type, int> ));
BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<op_hage(int, int)>::type, int const> ));
BOOST_MPL_ASSERT(( boost::is_same<boost::result_of<op_hage(int&, int)>::type, int> ));


void test()
{
    BOOST_CHECK( bar() == 1 );

    BOOST_CHECK( foo(3) == 3*3 );
    BOOST_CHECK( foo(2, 3) == 2*3 );

    BOOST_CHECK( hoge() == "hello" );
    BOOST_CHECK( hoge(4) == 4+4 );
    BOOST_CHECK( hoge(5, 6) == 5+6 );

    op_qoo(1,2)(3,4);
    op_qoo(3,5).hello();
}


int test_main(int, char*[])
{
    test();
    return 0;
}
