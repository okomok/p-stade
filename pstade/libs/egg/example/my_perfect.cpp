#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>

//[code_my_perfect
#include <boost/mpl/always.hpp>
#include <pstade/egg/perfect_strategy.hpp>
#include <pstade/egg/function_fwd.hpp>

/*<< Declare your strategy tag. >>*/
struct my_perfect : boost::mpl::always<pstade::egg::by_perfect> {};

/*<< `(2)(7)` means call operators can take is 2 or 7 arguments by perfect forwarding. >>*/
#define  PSTADE_EGG_PERFECT_STRATEGY_PARAMS (::my_perfect, (2)(7))
#include PSTADE_EGG_PERFECT_STRATEGY()
//]

#include <pstade/egg/pipable.hpp>
using namespace pstade::egg;

//[code_my_perfect_pipable
struct base_plus2_7
{
    typedef int result_type;

    int operator()(int i1, int i2, int i3) const
    {
        return i1 + i2 + i3;
    }

    int operator()(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8) const
    {
        return i1 + i2 + i3 + i4 + i5 + i6 + i7 + i8;
    }
};

result_of_pipable<base_plus2_7, ::my_perfect>::type const my_plus = PSTADE_EGG_PIPABLE({});

void test()
{
    /*<< Notice strategy is applied to pipable object: `my_plus`. >>*/
    BOOST_CHECK( (1|my_plus(2, 3)) == 1+(2+3) );
    BOOST_CHECK( (1|my_plus(2,3,4,5,6,7,8)) == 1+(2+3+4+5+6+7+8) );
}
//]


void pstade_minimal_test()
{
    ::test();
}
