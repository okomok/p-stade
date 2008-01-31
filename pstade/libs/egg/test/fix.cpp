#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/fix.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/use_deduced_form.hpp> // "incompletable" check.


#include <iostream>


namespace egg = pstade::egg;
using namespace egg;


struct unfixed_fib
{
    typedef int result_type;

    template<class F>
    int operator()(F f, int x) const
    {
        return x <= 1 ? 1 : (f(x-1) + f(x-2));
    }
};


struct T_uncurried_fact_
{
    typedef int result_type;

    template<class Fact, class I>
    int operator()(Fact fact, I i) const
    {
        // fact is the fixedpoint.
        return i == 0 ? 1 : i * fact(i-1);
    }
};

typedef result_of_curry2<T_uncurried_fact_>::type T_fact_;
PSTADE_POD_CONSTANT((T_fact_), fact_) = PSTADE_EGG_CURRY2({});

struct T_uncurried_wrap
{
    typedef int result_type;

    template<class F, class F_, class P>
    int operator()(F f, F_ f_, P p) const
    {
        // f_ is the fixedpoint
        int r = f(f_)(p); // => fact_(f_)(p) => fact_(fix wrap(fact_))(p)
        std::cout << r << std::endl;
        return r;
    }
};

typedef result_of_curry3<T_uncurried_wrap>::type T_wrap;
PSTADE_POD_CONSTANT((T_wrap), wrap) = PSTADE_EGG_CURRY3_L {} PSTADE_EGG_CURRY3_R;

struct T_uncurried_wrap2
{
    typedef int result_type;

    template<class F, class F_, class Ex, class P>
    int operator()(F f, F_ f_, Ex extra, P p) const
    {
        // f_(extra) is the fixedpoint.
        int r = f(f_(extra))(p);
        std::cout << r << std::endl;
        return r;
    }
};

typedef result_of_curry4<T_uncurried_wrap2>::type T_wrap2;
PSTADE_POD_CONSTANT((T_wrap2), wrap2) = PSTADE_EGG_CURRY3_L {} PSTADE_EGG_CURRY3_R;


void pstade_minimal_test()
{
    {
        BOOST_CHECK( 89 == fix( curry2(unfixed_fib()) )(10) );
    }
    {
        BOOST_CHECK( 3628800 == fix(fact_)(10) );

        typedef result_of_fix<T_fact_>::type T_fixed_fact;
        T_fixed_fact const fixed_fact = PSTADE_EGG_FIX(fact_);
        BOOST_CHECK( 3628800 == fixed_fact(10) );
    }
    {
        BOOST_CHECK( 3628800 == fix(wrap(fact_))(10) );
    }
    {
        int initialExtra = 1234;
        BOOST_CHECK( 3628800 == fix(wrap2(fact_))(initialExtra)(10) );
    }
}
