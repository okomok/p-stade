#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser.hpp>
#include <pstade/biscuit/algorithm/parse.hpp>


#include <string>
#include <pstade/oven.hpp>


using namespace pstade;
using namespace biscuit;


bool called = false;


struct action
{
    template< class SubRange, class Unused >
    void operator()(SubRange rng, Unused )
    {
        BOOST_CHECK( oven::equals(rng, std::string("actor")) );
        called = true;
    }
};


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
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
