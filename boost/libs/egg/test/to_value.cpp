

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/to_value.hpp>
#include "./egg_test.hpp"


#include "./check_is_result_of.hpp"
#include <memory>


#include "./using_egg.hpp"


CHECK_IS_RESULT_OF((int), T_to_value(int))
CHECK_IS_RESULT_OF((int), T_to_value(int&))
CHECK_IS_RESULT_OF((int), T_to_value(int const&))
CHECK_IS_RESULT_OF((int), T_to_value(int const))


void egg_test()
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
