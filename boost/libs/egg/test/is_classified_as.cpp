

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


CHECK_IS_RESULT_OF(bool, T_is_classified_as(char, std::ctype_base::mask const&))
CHECK_IS_RESULT_OF(bool, T_is_classified_as(wchar_t, std::ctype_base::mask const&, std::locale const&))


void egg_test()
{
    {
        BOOST_CHECK(is_classified_as('1', std::ctype_base::digit));
        BOOST_CHECK(is_classified_as('1', std::ctype_base::digit, std::locale()));
    }
}
