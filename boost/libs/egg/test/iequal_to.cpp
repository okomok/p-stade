

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/iequal_to.hpp>
#include "./egg_test.hpp"


#include "./check_is_result_of.hpp"


#include "./using_egg.hpp"


CHECK_IS_RESULT_OF((bool), T_iequal_to(char, char))


void egg_test()
{
    {
        BOOST_CHECK(iequal_to('a', 'A'));
        BOOST_CHECK(iequal_to('a', 'A', std::locale()));
    }
}
