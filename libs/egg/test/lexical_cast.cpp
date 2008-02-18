#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/lexical.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/egg/pstade/test.hpp>


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
