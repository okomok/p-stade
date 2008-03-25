

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/locale.hpp>
#include "./egg_test.hpp"


#include "./check_is_result_of.hpp"


#include "./using_egg.hpp"


CHECK_IS_RESULT_OF(bool, T_is_alpha(char, std::locale))
CHECK_IS_RESULT_OF(bool, T_is_upper(wchar_t))


void egg_test()
{
    {
        BOOST_CHECK(is_alpha('a'));
        BOOST_CHECK(is_upper('A', std::locale()));
    }
    {
        BOOST_CHECK(to_upper('a') == 'A');
        BOOST_CHECK(to_lower('A') == 'a');
        BOOST_CHECK(to_upper('a', std::locale()) == 'A');
        BOOST_CHECK(to_lower('A', std::locale()) == 'a');
    }
}
