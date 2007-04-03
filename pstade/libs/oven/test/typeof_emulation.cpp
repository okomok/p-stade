#define BOOST_TYPEOF_EMULATION


#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/typeof.hpp>


#include <string>
#include <pstade/oven/any_range.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/identities.hpp>
#include <boost/typeof/typeof.hpp>



namespace oven = pstade::oven;
using namespace oven;


template<class Range>
void test_tpl(Range& rng)
{
    {
        BOOST_AUTO_TPL(r, make_any_range(rng|identities|identities));
        BOOST_CHECK( equals(r, rng) );
    }
    {
        PSTADE_OVEN_AUTO_TPL(r, rng|identities|identities);
        BOOST_CHECK( equals(r, rng) );
    }
}


void test()
{
    std::string str("abcdefg");
    {
        BOOST_AUTO(r, make_any_range(str|identities|identities));
        BOOST_CHECK( equals(r, str) );
    }
    {
        PSTADE_OVEN_AUTO(r, str|identities|identities);
        BOOST_CHECK( equals(r, str) );
    }

    ::test_tpl(str);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
