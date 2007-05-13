#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/callable2.hpp>


#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/utility/result_of.hpp>
#include <string>


struct op_foo :
    pstade::callable2<op_foo>
{
    template< class Myself, class A0, class A1 >
    struct apply
    {
        typedef A0& type;
    };

    template< class Result, class A0, class A1 >
    Result call(A0& a0, A1& a1) const
    {
        a0 += a1;
        return a0;
    }
};


op_foo const foo = op_foo();


BOOST_MPL_ASSERT((boost::is_same<boost::result_of<op_foo(std::string, char)>::type, std::string const&>));
BOOST_MPL_ASSERT((boost::is_same<boost::result_of<op_foo(std::string const, char)>::type, std::string const&>));
BOOST_MPL_ASSERT((boost::is_same<boost::result_of<op_foo(std::string&, char)>::type, std::string&>));
BOOST_MPL_ASSERT((boost::is_same<boost::result_of<op_foo(std::string const&, char)>::type, std::string const&>));


struct op_foo_ :
    pstade::callable2<op_foo_>
{
    template< class Myself, class A0, class A1 >
    struct apply
    {
        typedef A1& type;
    };

    template< class Result, class A0, class A1 >
    Result call(A0& a0, A1& a1) const
    {
        a1 += a0;
        return a1;
    }
};

op_foo_ const foo_ = op_foo_();


BOOST_MPL_ASSERT((boost::is_same<boost::result_of<op_foo_(char, std::string)>::type, std::string const&>));
BOOST_MPL_ASSERT((boost::is_same<boost::result_of<op_foo_(char, std::string const)>::type, std::string const&>));
BOOST_MPL_ASSERT((boost::is_same<boost::result_of<op_foo_(char, std::string&)>::type, std::string&>));
BOOST_MPL_ASSERT((boost::is_same<boost::result_of<op_foo_(char, std::string const&)>::type, std::string const&>));


void test()
{
    {
        std::string s("hell");
        std::string x = foo(s, 'o');
        BOOST_CHECK( x == "hello" );
    }
    {
        std::string s("hell");
        std::string x = foo_('o', s);
        BOOST_CHECK( x == "hello" );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
