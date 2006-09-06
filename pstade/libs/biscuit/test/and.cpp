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
#include <pstade/oven.hpp>


using namespace pstade;
using namespace biscuit;


void test()
{
    {
        std::string src("hello, and_!");

        BOOST_CHECK((
            biscuit::match<
                seq<
                    chseq<'h','e','l','l','o',',',' '>,
                    and_<
                        chseq<'a','n','d','_'>,
                        repeat<any, 4>,
                        seq< char_<'a'>,any,any,char_<'_'> >
                    >,
                    char_<'!'>
                >
            >(src)
        ));

        BOOST_CHECK(( !
            biscuit::match<
                seq<
                    chseq<'h','e','l','l','o',',',' '>,
                    and_<
                        chseq<'a','n','d','_'>,
                        repeat<any, 4>,
                        chseq<'a','m','d','_'>
                    >,
                    char_<'!'>
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
