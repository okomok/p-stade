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


#include <boost/config.hpp>
#include <pstade/oven/equal.hpp>
#include <string>


struct is_abc
{
    template< class Range, class US >
    bool operator()(Range& rng, US&)
    {
        return pstade::oven::equal(rng, "abc");
    }
};


void test()
{
    using namespace pstade;
    using namespace biscuit;

    {
        std::string text("abc");
        BOOST_CHECK(( biscuit::match< require< repeat<any, 3>, is_abc > >(text) ));
    }
    {
        const std::string text("abz");
        BOOST_CHECK(( !biscuit::match< require< repeat<any, 3>, is_abc > >(text) ));
    }
    {
        std::string text("123");
        BOOST_CHECK(( biscuit::match< repeat<digit_com, 3> >(text) ));
    }


#if !defined(BOOST_NO_STD_WSTRING)
    {
        //BOOST_CHECK(( match< repeat<digit, 5> >(L"‚P‚Q‚R45") ));
        //BOOST_CHECK(( match< require< repeat<any, 5>, is_digit > >(L"‚P‚Q‚R45") ));
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
