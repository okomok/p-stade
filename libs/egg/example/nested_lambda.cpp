#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>


#include <pstade/egg/plus.hpp>
#include <pstade/egg/lambda/lazy_bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>


using namespace pstade::egg;
namespace bll = boost::lambda;


struct op_my_apply
{
    typedef int result_type;

    template<class F>
    int operator()(F f, int n) const
    {
        return f(n);
    }
};

op_my_apply const my_apply = {};

result_of_lazy<op_my_apply>::type const my_Apply = PSTADE_EGG_LAZY_L {} PSTADE_EGG_LAZY_R;


void pstade_minimal_test()
{
    pstade::result_of<op_lazy(op_plus const&)>::type Plus = lazy(plus);

    using bll::_1;
    using bll::_2;

    int a = 3, b = 5;

    // \x -> plus(7, x)
    BOOST_CHECK( Plus(7, _1)
        (a) == plus(7, a) );

    // \(x,y) -> plus(plus(x), y)
    BOOST_CHECK( Plus(Plus(4, _1), _2)
        (a, b) == plus(plus(4, a), b) );

    // currying
    // \x -> (\y -> plus(x, y))
    BOOST_CHECK( lambda_Bind(plus, _1, bll::protect(_1))
        (a)(b) == plus(a, b) );

    // complicated
    // \x -> my_apply(\y -> plus(x, y), plus(x, 3))
    BOOST_CHECK( my_Apply(lambda_Bind(plus, _1, bll::protect(_1)), Plus(_1, 3))
        (a) == plus(a, a+3) );
}
