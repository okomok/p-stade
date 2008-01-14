#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/intercepter.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/output_iterator.hpp"


#include <iterator> // back_inserter
#include <algorithm>
#include <string>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;
    {
        std::string sin("abcdefg");
        std::string sout;
        std::copy(sin.begin(), sin.end(), intercepter |= std::back_inserter(sout));
        BOOST_CHECK( sout.empty() );
    }
    {
        std::string sin("abcdefg");
        std::string sout;
        std::string sout2;
        std::copy(sin.begin(), sin.end(), intercepter(std::back_inserter(sout2)) |= std::back_inserter(sout));
        BOOST_CHECK( sout.empty() );
        BOOST_CHECK( sout2 == sin );
    }
    {
        std::string sout;
        test::output_iterator(intercepter |= std::back_inserter(sout), 123);
        test::output_iterator(intercepter(std::back_inserter(sout)) |= std::back_inserter(sout), 123);
    }
}
