#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/literal_range.hpp>


#include <vector>
#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/joint_range.hpp>
#include <pstade/oven/single_range.hpp>
#include <pstade/oven/c_str_range.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        literal_range<char, 12> rng("hello range");
        BOOST_CHECK( oven::equals(rng, std::string("hello range")) );
    }
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
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
