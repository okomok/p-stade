#include <pstade/detect_result_type.hpp>
#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/ambi.hpp>
#include <pstade/egg/curry.hpp>
#include <pstade/egg/uncurry.hpp>
#include <pstade/egg/compose.hpp>
#include <pstade/egg/indirect.hpp>
#include <pstade/egg/lazy.hpp>
#include <pstade/egg/memoize.hpp>
#include <pstade/egg/pipable.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <functional>
#include <pstade/minimal_test.hpp>


using namespace pstade::egg;


//[code_ambi_example
struct base_my_plus
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x + y;
    }
};

typedef result_of_ambi1<base_my_plus>::type T_my_plus;
T_my_plus const my_plus = PSTADE_EGG_AMBI({});

void test_ambi()
{
    BOOST_CHECK( my_plus(1, 2) == 3 );
    BOOST_CHECK( ( 1|my_plus(2) ) == 3 );

    std::plus<int> std_plus;
    BOOST_CHECK( ambi1(std_plus)(1, 2) == 3);
    BOOST_CHECK( ( 1|ambi1(std_plus)(2) ) == 3);
}
//]


//[code_curry_example
typedef result_of_curry2<T_my_plus>::type T_curried_plus;
T_curried_plus const curried_plus
    =
PSTADE_EGG_CURRY2_L PSTADE_EGG_AMBI({}) PSTADE_EGG_CURRY2_R /*< A macro invocation must be sandwiched using `_L` and `_R`. >*/
    ;

void test_curry()
{
    BOOST_CHECK( curried_plus(4)(9) == my_plus(4, 9) );
    BOOST_CHECK( curry2(my_plus)(4)(9) == 13 );
}
//]


//[code_indirect_example
result_of_uncurry<
    result_of_indirect<T_curried_plus const *>::type
>::type const another_plus
    =
PSTADE_EGG_UNCURRY_L
    /*<< `&curried_plus` is an /address constant expression/, so that `another_plus` can be /statically initialized/. >>*/
    PSTADE_EGG_INDIRECT(&curried_plus)
PSTADE_EGG_UNCURRY_R
    ;
//]

void test_indirect()
{
    BOOST_CHECK( another_plus(4, 9) == 13 );
}


//[code_lazy_example
result_of_lazy<base_my_plus>::type const my_Plus = PSTADE_EGG_LAZY({});

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
struct T_fib
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

T_fib const fib = {};

void test_memoize()
{
    BOOST_CHECK( fib(30) == 1346269 );
    BOOST_CHECK( memoize(fib)(30) == 1346269 );
}
//]


//[code_pipable_example
struct base_mult
{
    typedef int result_type;

    int operator()(int x) const
    {
        return x * x;
    }

    int operator()(int x, int y) const
    {
        return x * y;
    }

    int operator()(int x, int y, int z) const
    {
        return x * y * z;
    }
};

result_of_pipable<base_mult>::type const mult = PSTADE_EGG_PIPABLE({});

void test_pipable()
{
    BOOST_CHECK( ( 2|mult ) == 2 * 2 );
    BOOST_CHECK( ( 2|mult() ) == 2 * 2 );
    BOOST_CHECK( ( 2|mult(3)|mult(4) ) == 2 * 3 * 4 );
    BOOST_CHECK( ( 2|mult(3, 4) ) == 2 * 3 * 4 );

    // `|=` seems an "apply" operator.
    BOOST_CHECK( ( mult|=2 ) == 2 * 2 );
    BOOST_CHECK( ( mult()|=2 ) == 2 * 2 );
    BOOST_CHECK( ( mult|=mult|=2) == (2 * 2) * (2 * 2) );

    BOOST_CHECK( ( mult(3)|=2 ) == 2 * 3 );
    BOOST_CHECK( ( mult(3, 4)|= 2 ) == 2 * 3 * 4 );
}
//]
void test_pipable_pipable()
{
    base_mult const mult = {};
    BOOST_CHECK( (7 |( mult|(pipable|pipable(pipable)) ) ) == 7 * 7 );
}



void pstade_minimal_test()
{
    test_ambi();
    test_curry();
    test_indirect();
    test_lazy();
    test_memoize();
    test_pipable();
    test_pipable_pipable();
}
