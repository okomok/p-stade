#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/make_range.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/oven/equals.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("abc");
        BOOST_CHECK( equals(rng, make_range(rng)) );
        BOOST_CHECK( equals(rng, make_range(rng.begin(), rng.end())) );
    }
    {
        std::string rng;
        BOOST_CHECK( equals(rng, make_range(rng)) );
        BOOST_CHECK( equals(rng, make_range(rng.begin(), rng.end())) );
    }
}
