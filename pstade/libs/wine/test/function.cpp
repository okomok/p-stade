#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/function.hpp>


#include <string>
#include <boost/type_traits/is_convertible.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/test.hpp>


template<class A0, class A1>
struct baby_foo
{
    typedef A0& result_type;

    result_type operator()(A0& a0, A1& a1) const
    {
        a0 += a1;
        return a0;
    }
};

PSTADE_FUNCTION(foo, (baby_foo<_, _>))


PSTADE_TEST_IS_RESULT_OF((std::string&), op_foo(std::string&, char))
PSTADE_TEST_IS_RESULT_OF((std::string const&), op_foo(std::string, char))


struct baby_bar
{
    template<class A0, class A1 = void>
    struct apply
    {
        typedef apply type;
        typedef A0 result_type;

        result_type operator()(A0& a0, A1& a1) const
        {
            return a0 + a1;
        }
    };

    template<class A0>
    struct apply<A0>
    {
        typedef apply type;
        typedef A0 result_type;

        result_type operator()(A0& a0) const
        {
            return a0;
        }
    };

    std::string operator()() const
    {
        return "nullary";
    }
};

typedef pstade::function<baby_bar, std::string> op_bar;
PSTADE_CONSTANT(bar, (op_bar))

PSTADE_TEST_IS_RESULT_OF((int), op_bar(int&, char))
PSTADE_TEST_IS_RESULT_OF((double), op_bar(double&))
PSTADE_TEST_IS_RESULT_OF((std::string), op_bar())


#if 1 // !BOOST_WORKAROUND(BOOST_MSVC, == 1310) // VC7.1 ICE if 'boost::is_convertible' for enabling.

template<class A0, class A1 = pstade::enabler>
struct baby_buz
{
    typedef int result_type;
    result_type operator()(A0&) const
    {
        return 13;
    }
};

template<class A0>
struct baby_buz<A0, typename pstade::enable_if<boost::is_same<A0, const std::string> >::type>
{
    typedef std::string result_type;
    result_type operator()(std::string s) const
    {
        return s;
    }
};

PSTADE_FUNCTION(buz, (baby_buz<_>))

PSTADE_TEST_IS_RESULT_OF((int), op_buz(int&))
PSTADE_TEST_IS_RESULT_OF((std::string), op_buz(std::string))

#endif



template<class X, class A0>
struct specified_baby
{
    typedef A0& result_type;

    result_type operator()(A0& a) const
    {
        return a;
    }
};

template<class X>
struct op_specified :
    pstade::function< specified_baby<X, boost::mpl::_1> >
{ };

PSTADE_TEST_IS_RESULT_OF((int&), op_specified<double>(int&))



void test()
{
    {
        std::string s("abc");
        boost::result_of<op_foo(std::string&, char)>::type x = foo(s, '2');
        BOOST_CHECK( x == "abc2" );
    }
    {
        boost::result_of<op_bar(int, int)>::type x = bar(1, 2);
        BOOST_CHECK( x == 3 );
    }
    {
        boost::result_of<op_bar(int)>::type x = bar(1);
        BOOST_CHECK( x == 1 );
    }
    {
        boost::result_of<op_bar()>::type x = bar();
        BOOST_CHECK( x == "nullary" );
    }
#if 1 // !BOOST_WORKAROUND(BOOST_MSVC, == 1310) // VC7.1 ICE if 'boost::is_convertible' for enabling.
    {
        boost::result_of<op_buz(int)>::type x = buz(1);
        BOOST_CHECK( x == 13 );
        boost::result_of<op_buz(std::string)>::type y = buz(std::string("abc"));
        BOOST_CHECK( y == "abc" );
    }
#endif
    {
        int i = 12;
        BOOST_CHECK( op_specified<double>()(i) == 12 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
