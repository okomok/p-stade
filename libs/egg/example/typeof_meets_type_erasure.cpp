

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/expr.hpp>
#include "../test/egg_test.hpp"
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/egg/fuse.hpp>
#include <boost/egg/unfuse.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/egg/bll/result_of.hpp>


namespace bll = boost::lambda;
namespace egg = boost::egg;
using namespace egg;


//[code_typeof_meets_type_erasure
void test_expr()
{
    BOOST_AUTO(f,
        egg::expr<int(int, int)>(unfuse(fuse(bll::_1 + bll::_2))) );

    BOOST_CHECK( f(1,2) == 1+2 );
}
//]

void egg_test()
{
    ::test_expr();
}
