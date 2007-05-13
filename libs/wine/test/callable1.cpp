#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/callable1.hpp>


#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/utility/result_of.hpp>


struct op_foo :
    pstade::callable1<op_foo>
{
    template< class Myself, class A0 >
    struct apply
    {
        typedef A0& type;
    };

    template< class Result, class A0 >
    Result call(A0& a0) const
    {
        return a0;
    }
};


op_foo const foo = op_foo();


BOOST_MPL_ASSERT((boost::is_same<boost::result_of<op_foo(int)>::type, int const&>));
BOOST_MPL_ASSERT((boost::is_same<boost::result_of<op_foo(int const)>::type, int const&>));
BOOST_MPL_ASSERT((boost::is_same<boost::result_of<op_foo(int&)>::type, int&>));
BOOST_MPL_ASSERT((boost::is_same<boost::result_of<op_foo(int const&)>::type, int const&>));


void test()
{
    {
        int x = foo(1);
        BOOST_CHECK( x == 1 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
