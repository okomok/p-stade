#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/to_optional.hpp>
#include <pstade/minimal_test.hpp>


#include <memory>
#include <boost/optional.optional.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/egg/new_auto.hpp>
#include <pstade/test.hpp>


using namespace pstade::egg;


PSTADE_TEST_IS_RESULT_OF((boost::to_optional<int>), op_to_to_optional(int))
PSTADE_TEST_IS_RESULT_OF((boost::to_optional<int>), op_to_to_optional(int const))
PSTADE_TEST_IS_RESULT_OF((boost::to_optional<int>), op_to_to_optional(int&))
PSTADE_TEST_IS_RESULT_OF((boost::to_optional<int>), op_to_to_optional(int const&))



void pstade_minimal_test()
{
    {
        int i = 3;
        *to_optional(i) = 4;
        BOOST_CHECK( i == 3 );
    }
    {
        int const i = 3;
        BOOST_CHECK( *to_optional(i) == 3 );
    }
    {
        BOOST_CHECK( *to_optional(3) == 3 );
    }
}
