#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/lazy.hpp>
#include <pstade/egg/fix.hpp>
#include <pstade/egg/compose.hpp>
#include <pstade/egg/curry.hpp>
#include <pstade/egg/bll/placeholders.hpp>
#include <pstade/egg/bll/result_of.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>
#include <pstade/minimal_test.hpp>
#include <pstade/egg/const.hpp>
#include <boost/function.hpp>


namespace bll = boost::lambda;
namespace egg = pstade::egg;
using namespace egg;


struct T_inc
{
    typedef int result_type;

    result_type operator()(int i) const
    {
        return i + 1;
    }
};

PSTADE_EGG_CONST((T_inc), inc) = {};


void unnamed_recursion()
{
    using bll::_1;
    using bll::_2;

    int const two = 2, ten = 10;

    BOOST_CHECK(
        lazy(_1)(_2 - 1)(inc, ten) == inc(10-1)
    );

    BOOST_CHECK(
        compose(curry2(_2 * _1), _2)(two, ten)(two) == 10*2
    );

    BOOST_CHECK(
        (lazy(_2 * bll::protect(_1))(lazy(_1)(_2 - 1)))(inc, ten) == 10 * inc(10-1)
    );

    BOOST_CHECK(
        (_2 * lazy(_1)(_2 - 1))(inc, ten) == 10 * inc(10-1)
    );

//[code_unnamed_recursion
int r =
    fix2(
        bll::ret<int>(
            bll::if_then_else_return( _2 == 0,
                1,
                _2 * lazy(_1)(_2 - 1)
            )
        )
    ) (5);

BOOST_CHECK(r == 5*4*3*2*1);
//]
}


void pstade_minimal_test()
{
    ::unnamed_recursion();
}
