

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/lazy.hpp>
#include <boost/egg/bll.hpp>
#include "../test/egg_test.hpp"


#include <boost/egg/functional.hpp> // plus
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>


using namespace boost::egg;
namespace bll = boost::lambda;


struct T_my_apply
{
    typedef int result_type;

    template<class F>
    int operator()(F f, int n) const
    {
        return f(n);
    }
};

T_my_apply const my_apply = {};

result_of_lazy<T_my_apply>::type const my_Apply = BOOST_EGG_LAZY({});


void egg_test()
{
    boost::egg::result_of<T_lazy(T_plus const&)>::type Plus = lazy(plus);

    using bll::_1;
    using bll::_2;

    int a = 3, b = 5;

    // \x -> plus(7, x)
    BOOST_CHECK( Plus(7, _1)
        (a) == plus(7, a) );

    // \(x,y) -> plus(plus(x), y)
    BOOST_CHECK( Plus(Plus(4, _1), _2)
        (a, b) == plus(plus(4, a), b) );

    //[code_bll_bind_example
    /*<< This is currying in __BOOST_LAMBDA__. >>*/
    // \x -> (\y -> plus(x, y))
    BOOST_CHECK( lazy(bll_bind)(plus, _1, bll::protect(_1))
        (a)(b) == plus(a, b) );
    //]

    // complicated
    // \x -> my_apply(\y -> plus(x, y), plus(x, 3))
    BOOST_CHECK( my_Apply(lazy(bll_bind)(plus, _1, bll::protect(_1)), Plus(_1, 3))
        (a) == plus(a, a+3) );
}
