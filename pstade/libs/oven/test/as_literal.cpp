#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/as_literal.hpp>


#include <vector>
#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/jointed.hpp>
#include <pstade/oven/as_single.hpp>
#include <pstade/oven/as_c_str.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::vector<char> expected = std::string("hello range")|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable(
            "hello range"|as_literal,
            expected
        ) );
    }
#if 0
    {
        literal_range<char> rng("hello range");
        BOOST_CHECK( oven::equals(rng, std::string("hello range")) );
    }
#endif
    {
        BOOST_CHECK( oven::equals("hello range"|as_literal, std::string("hello range")) );
    }
    {
        wchar_t const str[] = L"hello range";
        BOOST_CHECK( oven::equals(str|as_literal, std::wstring(L"hello range")) );
    }

    {
        BOOST_CHECK( oven::equals(
            "hello\0range"|as_c_str,
            std::string("hello")
        ) );
        BOOST_CHECK( oven::equals(
            "hello\0range"|as_literal,
            std::string("hello")|jointed('\0'|as_single)|jointed(std::string("range"))
        ) );
    }
    {
        BOOST_CHECK(oven::equals(std::string("abcd"), std::string("abcd")|as_literal));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
