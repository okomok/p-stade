#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/curry.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/function.hpp>
#include <pstade/egg/functional.hpp> // plus


void pstade_minimal_test()
{
    namespace egg = pstade::egg;
    using namespace egg;

    boost::function<int(int)> f = curry2(plus)(1);
    BOOST_CHECK( f(2) == 3 );
}
