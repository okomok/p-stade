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
#include <pstade/egg/uncurry.hpp>
#include <pstade/egg/compose.hpp>
#include <pstade/egg/indirect.hpp>
#include <pstade/egg/memoize.hpp>
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
op_my_plus const my_plus = PSTADE_EGG_AUXILIARY_L {} PSTADE_EGG_AUXILIARY_R; /*< Sandwich base object initializer using macro. >*/

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
op_curried_plus const curried_plus
    = PSTADE_EGG_CURRY2_L PSTADE_EGG_AUXILIARY_L {} PSTADE_EGG_AUXILIARY_R PSTADE_EGG_CURRY2_R;

void test_curry()
{
    BOOST_CHECK( curried_plus(4)(9) == my_plus(4, 9) );
    BOOST_CHECK( curry2(my_plus)(4)(9) == 13 );
}
//]


//[code_indirect_example
result_of_uncurry<
    result_of_indirect<op_curried_plus const *>::type
>::type const another_plus
    =
PSTADE_EGG_UNCURRY_L
    PSTADE_EGG_INDIRECT_L
        /*<< `&curried_plus` is an /address constant expression/, so that `another_plus` can be /static-initialized/. >>*/
        &curried_plus
    PSTADE_EGG_INDIRECT_R
PSTADE_EGG_UNCURRY_R
    ;
//]

void test_indirect()
{
    BOOST_CHECK( another_plus(4, 9) == 13 );
}


//[code_memoize_example
struct op_fib_block
{
    typedef int result_type;

    template<class Fixed>
    int operator()(Fixed f, int x) const
    {
        return x <= 1 ? 1 : f(x-1) + f(x-2);
    }
};

op_fib_block const fib_block = {};

void test_memoize()
{
    BOOST_CHECK( memoize(fib_block)(30) == 1346269 );
}
//]



void pstade_minimal_test()
{
    test_auxiliary();
    test_curry();
    test_memoize();
    test_indirect();
}
