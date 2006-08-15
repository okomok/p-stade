#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>

#include <string>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/mpl/assert.hpp>


#include <pstade/egg/pipable.hpp>


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


PSTADE_EGG_PIPABLE(foo_pl, foo_impl)
PSTADE_EGG_PIPABLE(hoge_pl, hoge_impl)


void test()
{
    BOOST_CHECK( (3|foo_pl) == 3*3 );
    BOOST_CHECK( (3|foo_pl()) == 3*3 );
    BOOST_CHECK( (2|foo_pl(3)) == 2*3 );

    BOOST_CHECK( (4|hoge_pl) == 4+4 );
    BOOST_CHECK( (4|hoge_pl()) == 4+4 );
    BOOST_CHECK( (5|hoge_pl(6)) == 5+6 );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
