#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/with_position.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/biscuit.hpp>


namespace oven = pstade::oven;
namespace biscuit = pstade::biscuit;
using namespace biscuit;
using biscuit::plus;


struct on_unexpected
{
    template< class SubRange, class UserState >
    void operator()(SubRange rng, UserState& )
    {
        BOOST_CHECK(( rng.begin().get_position().line == 3 ));
        BOOST_CHECK(( rng.begin().get_currentline() == "AA#AA" )); // undocumented
    }
};


struct checker :
    seq<
        actor< any, on_unexpected >,
        nothing
    >
{ };


void test()
{
    {
        std::string src("AAAAA\nAAAAA\nAAAAA");

        BOOST_CHECK((
            biscuit::match< plus< or_< chset<'A','\n'>, checker > > >(src|oven::with_position)
        ));
    }

    {
        std::string src("AAAAA\nAAAAA\nAA#AA");

        BOOST_CHECK(( !
            biscuit::match< plus< or_< chset<'A','\n'>, checker > > >(src|oven::with_position)
        ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
