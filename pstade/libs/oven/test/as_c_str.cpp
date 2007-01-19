#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/as_c_str.hpp>


#include <string>
#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        boost::result_of<op_make_as_c_str(char const*)>::type rng = make_as_c_str("hello\0range");
        std::vector<char> expected = std::string("hello")|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable(rng, expected) );
    }
    {
        boost::result_of<op_make_as_c_str(char const*)>::type rng = make_as_c_str("hello\0range");
        BOOST_CHECK( oven::equals(rng, std::string("hello")) );
    }
    {
        BOOST_CHECK( oven::equals("hello\0range"|as_c_str, std::string("hello")) );
    }
    {
        wchar_t const *psz = L"hello range";
        BOOST_CHECK( oven::equals(psz|as_c_str, std::wstring(L"hello range")) );
    }
    {
        wchar_t const *psz = L"hello range";
        BOOST_CHECK( oven::equals(as_c_str(psz), std::wstring(L"hello range")) );
    }
    {
        std::string src("hello range");
        BOOST_CHECK( oven::equals(src.c_str()|as_c_str, src) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
