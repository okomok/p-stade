#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_CONCEPT_CHECK
#include <pstade/minimal_test.hpp>
#include <pstade/oven/as_literal.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/as_array.hpp>
#include <pstade/oven/distance.hpp>


using namespace pstade::oven;


void pstade_minimal_test()
{
    BOOST_CHECK( distance(as_array("abc\0de")) == 7 );   // contains the trailing null.
    BOOST_CHECK( distance(as_c_str("abc\0de")) == 3 );   // null means the end.
    BOOST_CHECK( distance(as_literal("abc\0de")) == 6 ); // null doesn't affect.
}
