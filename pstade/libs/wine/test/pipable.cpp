#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pipable.hpp>


struct my_fun_t
{
    typedef int result_type;

    int operator()(int x) const
    {
        return x + 1;
    }
};


PSTADE_PIPABLE(my_fun, my_fun_t)


struct your_fun_t
{
    typedef int result_type;

    int operator()(std::string str, int x, int y) const
    {
        return x + y;
    }
};


PSTADE_PIPABLE(your_fun, your_fun_t)


void test()
{
    BOOST_CHECK( (3|my_fun) == 4 );
    BOOST_CHECK( (3|my_fun()) == 4 );

    BOOST_CHECK( ("hello"| pstade::pipable(your_fun_t())(1, 2)) == 3 );

    BOOST_CHECK( ("hello"|your_fun(1, 2)) == 3 );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
