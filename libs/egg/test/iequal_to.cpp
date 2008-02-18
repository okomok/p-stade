#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/iequal_to.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;


PSTADE_TEST_IS_RESULT_OF((bool), T_iequal_to(char, char))


void pstade_minimal_test()
{
    using namespace pstade;

    {
        BOOST_CHECK(iequal_to('a', 'A'));
        BOOST_CHECK(iequal_to('a', 'A', std::locale()));
    }
}
