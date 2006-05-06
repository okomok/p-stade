#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/algorithm/match.hpp>
#include <pstade/biscuit/parser/utility/symbol.hpp>


#include <pstade/oven/null_terminate_range.hpp>


using namespace pstade;
using namespace biscuit;


PSTADE_BISCUIT_SYMBOL_PARSER(hello, "hello")
PSTADE_BISCUIT_SYMBOL_PARSER(bye, "bye")


void test()
{
    BOOST_CHECK( biscuit::match<hello>("hello"|oven::null_terminated) );
    BOOST_CHECK( biscuit::match<bye>("bye"|oven::null_terminated) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
