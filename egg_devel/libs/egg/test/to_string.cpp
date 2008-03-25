

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/to_string.hpp>
#include "./egg_test.hpp"


#include "./using_egg.hpp"


void egg_test()
{
    {
        BOOST_CHECK(to_string(1) == std::string("1"));
        BOOST_CHECK((1|to_string) == std::string("1"));
#if defined(BOOST_MSVC)
        BOOST_CHECK((1|to_wstring) == std::wstring(L"1"));
        BOOST_CHECK(to_wstring(1) == std::wstring(L"1"));
#endif
    }
}
