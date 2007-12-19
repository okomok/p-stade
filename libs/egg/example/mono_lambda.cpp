#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/mono.hpp>
#include <pstade/egg/lambda/result_of.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <pstade/minimal_test.hpp>
#include <functional>


namespace egg = pstade::egg;
using namespace egg;


void test()
{
    namespace bll = boost::lambda;

//[code_mono_example
BOOST_CHECK( std::not1( egg::mono<bool(int)>(bll::_1 != 12) ) (12) );
BOOST_CHECK( std::bind1st( egg::mono<boost::use_default(int, int)>(bll::_1 == bll::_2), 12 ) (12) );
//]

}


void pstade_minimal_test()
{
    test();
}
