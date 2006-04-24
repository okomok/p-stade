#include <boost/test/minimal.hpp>
#include <boost/spirit/phoenix/core/argument.hpp>
#include <boost/spirit/phoenix/function.hpp>
#include <pstade/const.hpp>


struct foo_impl
{
    typedef int result_type;

    int operator()() const
    {
        return 1;
    }

    template< class Arg1, class Arg2 = void >
    struct apply
    {
        typedef Arg1 type;
    };

    template< class Arg1 >
    Arg1 operator()(Arg1 _1) const
    {
        return _1 * _1;
    }

    template< class Arg1, class Arg2 >
    Arg1 operator()(Arg1 _1, Arg2 _2) const
    {
        return _1 * _2;
    }
};


template< class T >
struct instance
{
    static T& get()
    {
        static T x;
        return x;
    }
};


namespace {
    const boost::phoenix::function<foo_impl>& foo =
        instance< boost::phoenix::function<foo_impl> >::get();
}


void test_2006_03_02()
{
    BOOST_CHECK( foo()() == 1 );
    BOOST_CHECK( foo(3)() == 3*3 );
    BOOST_CHECK( foo(2, 3)() == 2*3 );

    using namespace boost::phoenix;
    BOOST_CHECK( foo(arg1)(pstade::const_(3)) == 3*3 );
}


int test_main(int, char*[])
{
    test_2006_03_02();
    return 0;
}
