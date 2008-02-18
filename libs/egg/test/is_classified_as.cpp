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


PSTADE_TEST_IS_RESULT_OF((bool), T_is_classified_as(char, std::ctype_base::mask const&))
PSTADE_TEST_IS_RESULT_OF((bool), T_is_classified_as(wchar_t, std::ctype_base::mask const&, std::locale const&))


void pstade_minimal_test()
{
    using namespace pstade;

    {
        BOOST_CHECK(is_classified_as('1', std::ctype_base::digit));
        BOOST_CHECK(is_classified_as('1', std::ctype_base::digit, std::locale()));
    }
}
