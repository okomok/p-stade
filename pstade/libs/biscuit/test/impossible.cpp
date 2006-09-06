#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser.hpp>


#include <string>
#include <pstade/biscuit/algorithm/match.hpp>


void test()
{
    using namespace pstade;
    using namespace biscuit;

    {
        BOOST_CHECK(( biscuit::match< or_<char_<'a'>, impossible> >(std::string("a")) ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
