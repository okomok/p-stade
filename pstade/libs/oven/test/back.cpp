#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/back.hpp>
#include <pstade/minimal_test.hpp>


#include <string>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string str("f12344513215b");
        BOOST_CHECK( back(str)  == 'b' );
        BOOST_CHECK( value_back(str)  == 'b' );

        back(str) = 'c';
        BOOST_CHECK( str == "f12344513215c" );
    }
}

