#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/auto_funptr.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/pod_constant.hpp>
#include <boost/lambda/lambda.hpp>
#include <pstade/egg/bll/result_of.hpp>


namespace egg = pstade::egg;
using namespace egg;



struct T_my_inc
{
    typedef int result_type;

    int operator()(int i) const
    {
        return i+1;
    }
};

PSTADE_POD_CONSTANT((T_my_inc), my_inc) = {};


struct T_my_plus
{
    typedef int result_type;

    int operator()(int i, int j) const
    {
        return i+j;
    }
};

PSTADE_POD_CONSTANT((T_my_plus), my_plus) = {};


struct T_my_two
{
    typedef int result_type;

    int operator()() const
    {
        return 2;
    }
};

PSTADE_POD_CONSTANT((T_my_two), my_two) = {};


int call_inc(int (*fp)(int), int i)
{
    return fp(i);
}

int call_plus(int (*fp)(int, int), int i, int j)
{
    return fp(i, j);
}

int call_two(int (*fp)())
{
    return fp();
}


void pstade_minimal_test()
{
    {
        namespace bl = boost::lambda;
        int r = ::call_plus(auto_funptr(bl::_1 + bl::_2), 1, 2);
        BOOST_CHECK(r == 3);
    }

    {
        int r = ::call_inc(auto_funptr(my_inc), 11);
        BOOST_CHECK(r == 12);
    }
    {
        int r = ::call_plus(auto_funptr(my_plus), 1, 2);
        BOOST_CHECK(r == 3);
    }
    {
        int r = ::call_two(auto_funptr(my_two));
        BOOST_CHECK(r == 2);
    }
}
