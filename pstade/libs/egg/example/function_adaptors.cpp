#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>

#include <pstade/egg/auxiliary.hpp>
#include <pstade/egg/curry.hpp>
#include <pstade/egg/compose.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <functional>


using namespace pstade::egg;


//[code_auxiliary_example
struct base_my_plus
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x + y;
    }
};

typedef result_of_auxiliary1<base_my_plus>::type op_my_plus; /*< Notice that `N` is not `2` but `1`. >*/
op_my_plus const my_plus = PSTADE_EGG_AUXILIARY({} BOOST_PP_EMPTY)(); /*< Don't forget a trailing `()`, a nullary macro invocation. >*/

void test_auxiliary()
{
    BOOST_CHECK( my_plus(1, 2) == 3 );
    BOOST_CHECK( ( 1|my_plus(2) ) == 3 );

    std::plus<int> std_plus;
    BOOST_CHECK( auxiliary1(std_plus)(1, 2) == 3);
    BOOST_CHECK( ( 1|auxiliary1(std_plus)(2) ) == 3);
}
//]


//[code_curry_example
typedef result_of_curry2<op_my_plus>::type op_curried_plus;
op_curried_plus const curried_plus = PSTADE_EGG_CURRY2(PSTADE_EGG_AUXILIARY({} BOOST_PP_EMPTY))();

void test_curry()
{
    BOOST_CHECK( curried_plus(4)(9) == my_plus(4, 9) );
    BOOST_CHECK( curry2(my_plus)(4)(9) == 13 );
}
//]

void pstade_minimal_test()
{
    test_auxiliary();
    test_curry();
}
