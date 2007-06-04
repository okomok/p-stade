#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/v1_tests.hpp"
#include <pstade/oven/lower_chars.hpp>
#include <pstade/oven/upper_chars.hpp>
#include <pstade/oven/const_refs.hpp>
#include <pstade/oven/wide_chars.hpp>
#include <pstade/oven/narrow_chars.hpp>


#include <string>
#include "./detail/v1_core.hpp"


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string ans("abcdefg");
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            std::string("AbCdEFg")|lower_chars|const_refs,
            expected
        ) );
    }
    {
        std::string ans("ABCDEFG");
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            std::string("AbCdEFg")|upper_chars|const_refs,
            expected
        ) );
    }

#if !defined(__MINGW32__)
    {
        std::string ans("abcdefg");
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            std::wstring(L"abcdefg")|narrow_chars|const_refs,
            expected
        ) );
    }
    {
        std::wstring ans(L"abcdefg");
        std::vector<wchar_t> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            std::string("abcdefg")|wide_chars|const_refs,
            expected
        ) );
    }
#endif

    {
        BOOST_CHECK( equals(
            std::string("AbCdEFG")|lower_chars,
            std::string("abcdefg")
        ) );
    }
    {
        BOOST_CHECK( equals(
            std::string("AbCdEFG")|lower_chars(std::locale()),
            std::string("abcdefg")
        ) );
    }
    {
        BOOST_CHECK( equals(
            std::string("AbCdEFG")|upper_chars,
            std::string("ABCDEFG")
        ) );
    }
    {
        BOOST_CHECK( equals(
            std::string("AbCdEFG")|upper_chars(std::locale()),
            std::string("ABCDEFG")
        ) );
    }

#if !defined(__MINGW32__)
    {
        BOOST_CHECK( equals(
            std::string("abcdefg")|wide_chars,
            std::wstring(L"abcdefg")
        ) );

        BOOST_CHECK( equals(
            std::string("abcdefg")|wide_chars(std::locale()),
            std::wstring(L"abcdefg")
        ) );
    }
    {
        BOOST_CHECK( equals(
            std::wstring(L"abcdefg")|narrow_chars,
            std::string("abcdefg")
        ) );
    }
    {
        BOOST_CHECK( equals(
            std::wstring(L"abcdefg")|narrow_chars(std::locale()),
            std::string("abcdefg")
        ) );
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
