#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_EGG_MAX_ARITY 8
#define BOOST_EGG_MAX_LINEAR_ARITY 20
#include <boost/egg/detail/egg.hpp>
#include <boost/egg/detail/egg_pending.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


using namespace pstade::egg;

struct my
{
    my(int,int,int,int,int,int,int,int) {}
};

struct T_your
{
    int operator()(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) const
    {
        return 3;
    }
};

result_of_return<T_your, int, by_cref>::type const your = BOOST_EGG_RETURN_L {} BOOST_EGG_RETURN_R;


void pstade_minimal_test()
{
    my m = pstade::egg::constructor(1,2,3,4,5,6,7,8);
    BOOST_CHECK( 3 == your(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20) );
}