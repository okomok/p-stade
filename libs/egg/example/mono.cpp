

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/mono.hpp>
#include <functional> // not1, bind1st


#include "./using_bll.hpp"
#include "./egg_example.hpp"


//[code_example_mono
void egg_example()
{
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
}
//]
