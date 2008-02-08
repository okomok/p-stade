#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/expr.hpp>
#include <pstade/minimal_test.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/egg/fuse.hpp>
#include <pstade/egg/unfuse.hpp>
#include <boost/typeof/typeof.hpp>
#include <pstade/egg/bll/result_of.hpp>


namespace bll = boost::lambda;
namespace egg = pstade::egg;
using namespace egg;


//[code_typeof_meets_type_erasure
void test_expr()
{
    BOOST_AUTO(f,
        egg::expr<int(int, int)>(unfuse(fuse(bll::_1 + bll::_2))) );

    BOOST_CHECK( f(1,2) == 1+2 );
}
//]

void pstade_minimal_test()
{
    ::test_expr();
}
