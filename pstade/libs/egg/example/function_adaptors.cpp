#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <pstade/detail/before_mpl_has_xxx.hpp>
#include <pstade/minimal_test.hpp>

#include <pstade/egg/auxiliary.hpp>
#include <pstade/egg/curry.hpp>
#include <pstade/egg/uncurry.hpp>
#include <pstade/egg/compose1.hpp>
#include <pstade/egg/indirect.hpp>
#include <pstade/egg/lazy.hpp>
#include <pstade/egg/memoize.hpp>
#include <pstade/egg/pipable.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
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
    =
PSTADE_EGG_CURRY2_L
    PSTADE_EGG_AUXILIARY_L {} PSTADE_EGG_AUXILIARY_R
PSTADE_EGG_CURRY2_R
    ;

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


//[code_lazy_example
result_of_lazy<base_my_plus>::type const
    my_Plus = PSTADE_EGG_LAZY_L {} PSTADE_EGG_LAZY_R;

void test_lazy()
{
    namespace bll = boost::lambda;

    /*<< Boost1.35 or later won't require `make_const`. >>*/
    BOOST_CHECK( my_Plus(bll::_1, 3)(bll::make_const(2)) == 2+3 );

    int two = 2, four = 4;
    BOOST_CHECK( my_Plus(my_Plus(bll::_1, 3), my_Plus(bll::_2, bll::_1))
        (two, four) == (2+3)+(4+2) );
}
//]


//[code_memoize_example
struct op_fib
{
    typedef int result_type;

    template<class Fixed>
    int operator()(Fixed f, int x) const
    {
        return x <= 1 ? 1 : f(x-1) + f(x-2);
    }

    int operator()(int x) const
    {
        return (*this)(*this, x);
    }
};

op_fib const fib = {};

void test_memoize()
{
    BOOST_CHECK( fib(30) == 1346269 );
    BOOST_CHECK( memoize(fib)(30) == 1346269 );
}
//]


//[code_pipable_example
struct op_multiplies
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x * y;
    }

    int operator()(int x, int y, int z) const
    {
        return x * y * z;
    }
};

op_multiplies const multiplies = {};

void test_pipable()
{
    BOOST_CHECK( ( 2|pipable(multiplies)(3) ) == 2 * 3 );
    BOOST_CHECK( ( 2|pipable(multiplies)(3, 4) ) == 2 * 3 * 4 );
}
//]



void pstade_minimal_test()
{
    test_auxiliary();
    test_curry();
    test_indirect();
    test_lazy();
    test_memoize();
    test_pipable();
}
