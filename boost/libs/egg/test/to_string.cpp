#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/to_string.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;


void pstade_minimal_test()
{
    {
        using namespace pstade;
        BOOST_CHECK(to_string(1) == std::string("1"));
        BOOST_CHECK((1|to_string) == std::string("1"));
#if defined(BOOST_MSVC)
        BOOST_CHECK((1|to_wstring) == std::wstring(L"1"));
        BOOST_CHECK(to_wstring(1) == std::wstring(L"1"));
#endif
    }
}
