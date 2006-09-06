#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser.hpp>
#include <pstade/biscuit/algorithm/match.hpp>
#include <pstade/biscuit/algorithm/parse.hpp>


#include <string>
#include <pstade/oven.hpp>


using namespace pstade;
using namespace biscuit;


PSTADE_BISCUIT_SYMBOL(hello, "hello")
typedef as_lower< hello > ihello;

void test()
{
    BOOST_CHECK(( biscuit::match< ihello >(std::string("hElLo")) ));
}

int test_main(int, char*[])
{
    ::test();

    return 0;
}

