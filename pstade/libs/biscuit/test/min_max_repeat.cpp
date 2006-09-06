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
#include <pstade/oven.hpp>


using namespace pstade;
using namespace biscuit;


void test()
{
    {
        BOOST_CHECK((
            biscuit::match<
                max_repeat< char_<'a'>, 3 >
            >(std::string("aaa"))
        ));
    }

    {
        BOOST_CHECK((
            biscuit::match<
                max_repeat< char_<'a'>, 3 >
            >(std::string("a"))
        ));
    }

    {
        BOOST_CHECK((
            biscuit::match<
                max_repeat< char_<'a'>, 3 >
            >(std::string())
        ));
    }

    {
        BOOST_CHECK((
            biscuit::match<
                min_repeat< char_<'a'>, 3 >
            >(std::string("aaa"))
        ));
    }

    {
        BOOST_CHECK(( !
            biscuit::match<
                min_repeat< char_<'a'>, 3 >
            >(std::string("aa"))
        ));
    }
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
