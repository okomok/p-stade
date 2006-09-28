#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/c_str_range.hpp>


#include <string>
#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        c_str_range<char const> rng("hello\0range");
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
        std::string src("hello range");
        BOOST_CHECK( oven::equals(src.c_str()|as_c_str, src) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
