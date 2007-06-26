#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/provide_sig.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/lambda/core.hpp>
#include <boost/lambda/bind.hpp>


struct op0 : pstade::egg::provide_sig
{
    template<class Sig>
    struct result;

    template<class F, class A0>
    struct result<F(A0)>
    {
        typedef int type;
    };

    int operator()(int i) const { return i; }
};


void pstade_minimal_test()
{
    namespace bll = boost::lambda;

    int i = 3;
    BOOST_CHECK( bll::bind(op0(), bll::_1)(i) == 3 );
}
