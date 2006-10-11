#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/constant_range.hpp>


#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/identity_range.hpp>


namespace oven = pstade::oven;
using namespace oven;


// Assume you want to keep 'rng' from
// unintentional modifications.

template< class Range >
void legacy_way(Range const& rng)
{
    *boost::begin(rng) = 'x';
    *boost::const_begin(rng) = 'x';
}

template< class Range >
void modern_way(Range& rng)
{
    constant_range<Range> safe_rng(rng);
    *boost::begin(safe_rng) = 'x';
}

void test()
{
    {
        std::string str("hello, constant_range!");
        BOOST_CHECK(oven::equals(str, str|constants));
        ::legacy_way(str|identities); // oops, compiles.
        // ::modern_way(str|identities); // error
        // ::legacy_way(str|identities|constants); // error
    }
    {
        std::string rng("urifoqjfoqnfeionfqo");
        std::vector<char> expected = rng|copied;
        BOOST_CHECK(oven::test_RandomAccess_Readable(rng, expected));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
