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
#include <pstade/biscuit/alias.hpp>


using namespace biscuit;


struct infinite :
    identity<infinite>
{ };


struct infinite2 :
    seq<infinite2>
{ };


void test()
{

}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
