#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/v1_tests.hpp"
#include <pstade/oven/pointed.hpp>


#include <cstring>
#include <string>
#include <vector>
#include <boost/range.hpp>
#include "./detail/v1_core.hpp"
#include <pstade/oven/as_c_str.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::vector<char> rng = std::string("abcdefghijklmn")|copied;
        std::vector<char> expected = rng|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|pointed,
            expected
        ) );
    }
    {
        std::vector<int> vec;
        BOOST_CHECK(( boost::empty(vec|pointed) ));
    }
    {
        std::string const src("hello, pointer_range");
        std::vector<char> vec;
        vec.resize(oven::distance(src) + 1);
        std::strcpy(vec|pointed|begin, src.c_str());
        BOOST_CHECK(( oven::equals(vec|as_c_str, src) ));
    }
#if 1 // 'std::string' isn't guaranteed to be contiguous by the standard, but always works.
    {
        std::string rng("abcdefghijklmn");
        std::vector<char> expected = rng|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|pointed,
            expected
        ) );
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
