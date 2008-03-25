

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/bind_n.hpp>
#include <boost/egg/placeholders.hpp>
#include "./egg_test.hpp"


#include <boost/egg/const.hpp>


#include "./using_egg.hpp"


struct T_my_plus
{
    typedef int result_type;

    int operator()(int i, int j, int k) const
    {
        return i+j+k;
    }
};

BOOST_EGG_CONST((T_my_plus), my_plus) = {};


typedef result_of_bind3<T_my_plus, boost::use_default, int, int, placeholders::TT_1>::type T_bplus;
BOOST_EGG_CONST((T_bplus), bplus) = BOOST_EGG_BIND_L {}, 7, 8, BOOST_EGG_PLACEHOLDER BOOST_EGG_BIND_R;


struct T_my_2times
{
    typedef int result_type;

    int operator()(int i) const
    {
        return 2*i;
    }
};

BOOST_EGG_CONST((T_my_2times), my_2times) = {};


void egg_test()
{
    using namespace placeholders;
    BOOST_CHECK(bind3(my_plus, _1, _1, 3)(1) == 1+1+3);
    BOOST_CHECK(X_bind3<int>()(my_plus, 1, 2, 3)() == 1+2+3);
    BOOST_CHECK(bplus(9) == 7+8+9);
    BOOST_CHECK(bind1(my_2times, bind1(my_2times, _1))(9) == 2*2*9);
}
