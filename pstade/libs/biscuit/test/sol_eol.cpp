#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser.hpp>
#include <pstade/biscuit/algorithm/match.hpp>


#include <string>
#include <pstade/oven.hpp>


using namespace pstade;
using namespace biscuit;


void test()
{
    {
        BOOST_CHECK((
            biscuit::match<
                seq<sol, chseq<'a','b','c'>, eol>
            >(std::string("abc"))
        ));
    }

    {
        BOOST_CHECK((
            biscuit::match<
                seq<sol, eol>
            >(std::string(""))
        ));
    }

    {
        BOOST_CHECK((
            biscuit::match<
                repeat< seq<sol, chseq<'A','A'>, eol>, 3 >
            >(std::string("AA\nAA\nAA\n"))
        ));
    }

    {
        BOOST_CHECK((
            biscuit::match<
                repeat< seq<sol, chseq<'A','A'>, eol>, 3 >
            >(std::string("AA\nAA\nAA"))
        ));
    }
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
