

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/lexical.hpp>
#include "./egg_test.hpp"


#include "./using_egg.hpp"


void egg_test()
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
