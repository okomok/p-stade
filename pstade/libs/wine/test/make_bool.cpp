#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/make_bool.hpp>
#include <pstade/minimal_test.hpp>


using namespace pstade;


void pstade_minimal_test()
{
    BOOST_CHECK( make_bool(3) );
    BOOST_CHECK( !make_bool(0) );
}
