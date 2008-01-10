#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/lexical.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;


void pstade_minimal_test()
{
    {
        BOOST_CHECK( X_lexical_cast<std::string>()(12) == "12" );
        BOOST_CHECK( X_lexical_cast<int>()(std::string("12")) == 12 );
    }
#if 0
    {
        BOOST_CHECK( egg::lexical_cast<std::string>(12) == "12" );
        BOOST_CHECK( egg::lexical_cast<int>(std::string("12")) == 12 );
    }
#endif
}
