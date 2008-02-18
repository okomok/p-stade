#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/locale.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;


PSTADE_TEST_IS_RESULT_OF((char), T_to_upper(char, std::locale))
PSTADE_TEST_IS_RESULT_OF((wchar_t), T_to_upper(wchar_t))


void pstade_minimal_test()
{
    using namespace pstade;

    {
        BOOST_CHECK(to_upper('a') == 'A');
        BOOST_CHECK(to_upper('a', std::locale()) == 'A');
    }
}
