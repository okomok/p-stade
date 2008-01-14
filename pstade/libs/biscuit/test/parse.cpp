#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/algorithm/parse.hpp>
#include <pstade/biscuit/parser.hpp>


#include <string>
#include <pstade/biscuit/alias.hpp>
using namespace biscuit;


void test()
{
    { // compile check only
        std::string str;
        biscuit::parse<eps>(str);
        biscuit::parse<eps>(str, biscuit::null_state);

        biscuit::match_results<std::string> r;
        biscuit::results_parse<eps>(str, r);
        biscuit::results_parse<eps>(str, r, biscuit::null_state);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
