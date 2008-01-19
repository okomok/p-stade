#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/to_value.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>
#include <memory>


namespace egg = pstade::egg;
using namespace egg;


PSTADE_TEST_IS_RESULT_OF((int), T_to_value(int))
PSTADE_TEST_IS_RESULT_OF((int), T_to_value(int&))
PSTADE_TEST_IS_RESULT_OF((int), T_to_value(int const&))
PSTADE_TEST_IS_RESULT_OF((int), T_to_value(int const))


void pstade_minimal_test()
{
    {
        int i = 3;
        BOOST_CHECK( to_value(i) == 3 );
        BOOST_CHECK( (i|to_value) == 3 );
        BOOST_CHECK( (i|to_value()) == 3 );
        BOOST_CHECK( to_value(3) == 3 );
    }
    {
        std::auto_ptr<int> x(new int(3));
        std::auto_ptr<int> x_ = x|to_value;
        x_ = x_|to_value();
        x_ = to_value(x_);
    }
}
