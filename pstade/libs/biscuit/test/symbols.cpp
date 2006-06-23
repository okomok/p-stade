#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/algorithm/match.hpp>
#include <pstade/biscuit/parser.hpp>
#include <pstade/biscuit/parser/dynamic/symbols.hpp>


#include <string>
#include <vector>


using namespace pstade;
using namespace biscuit;


struct my_ftor
{
    template< class UserState >
    void operator()(int& v, UserState& ) const
    {
        v += 10;
    }
};


void test()
{
    std::map<std::string, int> syms;
    syms["hello"] = 1;
    syms["cheap"] = 2;
    syms["symbols"] = 3;

    BOOST_CHECK((
        biscuit::match< seq< symbols<>, chseq<'!'> > >(std::string("hello!"), syms)
    ));

    BOOST_CHECK((
        biscuit::match< seq< chseq<'*'>, symbols<identity_fun>, chseq<'*'> > >(std::string("*symbols*"), syms)
    ));

    BOOST_CHECK((
        biscuit::match< seq< symbols<identity_fun, ::my_ftor>, chseq<'!'> > >(std::string("hello!"), syms)
    ));
    BOOST_CHECK(( syms["hello"] == 11 ));
    BOOST_CHECK(( syms["cheap"] == 2 ));
    BOOST_CHECK(( syms["symbols"] == 3 ));
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
