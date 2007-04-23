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


#include <string>
#include <pstade/oven/alias.hpp>
#include <pstade/biscuit/alias.hpp>


using namespace biscuit;


void test()
{
    {
        BOOST_CHECK((
            biscuit::match<
                seq< begin, end >
            >(std::string())
        ));


        BOOST_CHECK((
            biscuit::match<
                seq< begin, chseq<'a','b','c'>, end >
            >(std::string("abc"))
        ));

        BOOST_CHECK(( !
            biscuit::match<
                seq< chseq<'a'>, begin, chseq<'b','c'> >
            >(std::string("abc"))
        ));

        BOOST_CHECK(( !
            biscuit::match<
                seq< chseq<'a'>, end, chseq<'b','c'> >
            >(std::string("abc"))
        ));
    }
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
