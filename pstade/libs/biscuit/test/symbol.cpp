#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/algorithm/match.hpp>
#include <pstade/biscuit/parser/utility/symbol.hpp>


#include <string>


using namespace pstade;
using namespace biscuit;


PSTADE_BISCUIT_SYMBOL(hello, "hello")
PSTADE_BISCUIT_SYMBOL(bye, L"bye")


void test()
{
    BOOST_CHECK( biscuit::match<hello>(std::string("hello")) );
    BOOST_CHECK( biscuit::match<bye>(std::wstring(L"bye")) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
