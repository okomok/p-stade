#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser.hpp>
#include <pstade/biscuit/action.hpp>
#include <pstade/biscuit/algorithm/parse.hpp>


#include <string>
#include <pstade/oven.hpp>


using namespace pstade;
using namespace biscuit;


bool called = false;
bool called2 = false;


struct action
{
    template< class SubRange, class _ >
    void operator()(SubRange rng, _)
    {
        BOOST_CHECK( oven::equals(rng, std::string("actor")) );
        called = true;
    }
};


PSTADE_BISCUIT_ACTION(action2,
    BOOST_CHECK( oven::equals(rng, std::string("actor")) );
    called2 = true;
)


void test()
{
    {
        std::string src("hello, actor!");
        biscuit::parse<
            seq<
                chseq<'h','e','l','l','o',',',' '>,
                actor< star_before< any, chseq<'!'> >, ::action >
            >
        >(src);

        BOOST_CHECK( ::called );
    }

    {
        std::string src("hello, actor!");
        biscuit::parse<
            seq<
                chseq<'h','e','l','l','o',',',' '>,
                actor< star_before< any, chseq<'!'> >, ::action2 >
            >
        >(src);

        BOOST_CHECK( ::called2 );
    }
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
