

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detect_result_type.hpp>


#include <boost/egg/return.hpp>
#include <boost/egg/mono.hpp>
#include "./egg_test.hpp"


#include BOOST_EGG_SUPPRESS_WARNING_BEGIN()
#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp>
#include BOOST_EGG_SUPPRESS_WARNING_END()


#include "./using_egg.hpp"
namespace bll = boost::lambda;


struct F { int operator()(int i) const { return i; } };
F const f = {};

struct G { typedef int result_type; int operator()(int i) const { return i; } };
G const g = {};


void egg_test()
{
    {
        bll::bind(f, bll::_1);
        // bll::bind(f, 1); // error!
    }
    {
        BOOST_CHECK( bll::bind(egg::mono<int(int)>(f), 1)() == 1 );
        BOOST_CHECK( bll::bind(egg::return_<int>(g), 1)() == 1 );
    }
}
