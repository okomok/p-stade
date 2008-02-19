

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/bll/bind.hpp>
#include <boost/egg/bll/unlambda.hpp>
#include <boost/egg/bll/placeholders.hpp>
#include <boost/egg/bll/result_of.hpp>
#include "./egg_test.hpp"


#include <boost/egg/lazy.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/functional.hpp> // plus
#include <boost/egg/to_ref.hpp>
#include "./check_is_result_of.hpp"


using namespace boost::egg;


int sum_of_args_1(int a) { return a; }

int my_minus(int i, int j) { return i - j; }

int big_arity(int, int, int, int, int, int, int, int, int)
{
    return 3;
}

void egg_test()
{
    {
        boost::egg::result_of_<T_bll_bind(T_plus, T_bll_1, int)>::type b =
            bll_bind(plus, bll_1, 10);

        BOOST_CHECK( b(20|to_ref) == 30 );
        BOOST_CHECK( bll_bind(&big_arity, 1,2,3,4,bll_1,6,bll_2,8,9)(3|to_ref, 4|to_ref) == 3 );
    }
    {
#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        int two = 2;
        BOOST_CHECK(bll_bind(my_minus, 10, bll_1)(two) == 8);
#endif
    }
    {
        typedef
            boost::egg::result_of_<T_bll_bind(int (*)(int), int)>::type
        b_t;

        b_t b = bll_bind(&sum_of_args_1, 10);

        CHECK_IS_RESULT_OF((int), b_t())

        boost::egg::result_of_<b_t()>::type b_ = b();
        BOOST_CHECK(b_ == 10);
    }
    {
        T_plus f = bll_unlambda(plus); // no effect
        BOOST_CHECK( f(1,2) == 3 );

        // unlambda it!
        boost::egg::result_of_<T_bll_unlambda(T_bll_1)>::type u = bll_unlambda(bll_1);
        int i = 10;
        BOOST_CHECK( boost::lambda::bind(u, bll_1)(i) == 10 );
    }
    {
        int i = 3;
        int (*pf)(int,int) = &my_minus;
        BOOST_CHECK( lazy(bll_bind)(bll_1, boost::lambda::protect(bll_1), 10)(pf)(i) == -7 );
    }
}
