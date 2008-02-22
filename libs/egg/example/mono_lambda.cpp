

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/mono.hpp>
#include <boost/egg/bll/result_of.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include "../test/egg_test.hpp"
#include <functional>


namespace egg = boost::egg;
using namespace egg;


void test()
{
    namespace bll = boost::lambda;

//[code_mono_example
BOOST_CHECK(
    std::not1(
        egg::mono<bool(int const&)>(bll::_1 != 12)
    ) (12)
);
BOOST_CHECK(
    std::bind1st(
        egg::mono<boost::use_default(int const&, int const&)>(bll::_1 == bll::_2),
        12
    ) (12)
);
//]

}


void egg_test()
{
    test();
}
