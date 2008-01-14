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
#include <pstade/oven/equals.hpp>


#include <pstade/biscuit/alias.hpp>
#include <pstade/oven/alias.hpp>
using namespace biscuit;


void test()
{
    {
        std::string src("hello, before!");

        BOOST_CHECK((
            biscuit::match<
                seq<
                    repeat<any, 7>,
                    before< chseq<'b','e'> >,
                    chseq<'b','e','f','o','r','e','!'>
                >
            >(src)
        ));

        BOOST_CHECK(( oven::equals(
            biscuit::parse<
                seq<
                    repeat<any, 7>,
                    before< chseq<'b','e'> >
                >
            >(src),
            std::string("hello, ")
        ) ));

        BOOST_CHECK((
            biscuit::match<
                seq<
                    repeat<any, 7>,
                    before< chseq<'b','e'> >,
                    before< chseq<'b','e'> >,
                    before< chseq<'b','e'> >,
                    chseq<'b','e','f','o','r','e','!'>
                >
            >(src)
        ));
    }

    {
        std::string src("hello, after!");

        BOOST_CHECK((
            biscuit::match<
                seq<
                    repeat<any, 9>,
                    after< chseq<'a','f'>, 2 >,
                    chseq<'t','e','r','!'>
                >
            >(src)
        ));

        BOOST_CHECK(( oven::equals(
            biscuit::parse<
                seq<
                    repeat<any, 9>,
                    after< chseq<'a','f'>, 2 >
                >
            >(src),
            std::string("hello, af")
        ) ));

        BOOST_CHECK((
            biscuit::match<
                seq<
                    repeat<any, 9>,
                    after< chseq<'a','f'>, 2 >,
                    after< chseq<'a','f'>, 2 >,
                    after< chseq<'a','f'>, 2 >,
                    chseq<'t','e','r','!'>
                >
            >(src)
        ));
    }
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
