#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/const_function.hpp>


#include <boost/utility/result_of.hpp>


using namespace pstade;


struct my_op
{
    typedef int result_type;

    int operator()(int i, int j) const
    {
        return i + j;
    }

    int operator()(int i) const
    {
        return i;
    }

    int operator()() const
    {
        return 3;
    }
};


int my_fun(int i)
{
    return i;
}


void test()
{
    my_op const f = { };
    {
        boost::result_of<PSTADE_CONST_FUNCTION(my_op)(int, int)>::type r = f(10, 12);
        BOOST_CHECK(r == 22);
    }
    {
        boost::result_of<PSTADE_CONST_FUNCTION(my_op)(int)>::type r = f(10);
        BOOST_CHECK(r == 10);
    }
    {
        boost::result_of<PSTADE_CONST_FUNCTION(my_op)()>::type r = f();
        BOOST_CHECK(r == 3);
    }
    {
        typedef int (*pf_t)(int);
        pf_t const pf = &::my_fun;
        boost::result_of<PSTADE_CONST_FUNCTION(pf_t)(int)>::type r = pf(12);
        BOOST_CHECK(r == 12);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
