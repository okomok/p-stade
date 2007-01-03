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
#include <pstade/tests.hpp>


template<class A0, class A1>
struct baby_foo
{
    typedef A0& result;

    static result call(A0& a0, A1& a1)
    {
        a0 += a1;
        return a0;
    }
};


PSTADE_FUNCTION(foo, (baby_foo<_1, _2>))


PSTADE_TEST_IS_RESULT_OF((std::string&), op_foo(std::string&, char))
PSTADE_TEST_IS_RESULT_OF((std::string const&), op_foo(std::string, char))


void test()
{
    {
        std::string s("abc");
        boost::result_of<op_foo(std::string&, char)>::type x = foo(s, '2');
        BOOST_CHECK( x == "abc2" );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
