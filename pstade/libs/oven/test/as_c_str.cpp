#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/as_c_str.hpp>


#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        BOOST_CHECK( oven::equals("hello\0range"|as_c_str, std::string("hello")) );
    }
    {
        wchar_t const str[] = L"hello range";
        BOOST_CHECK( oven::equals(str|as_c_str, std::wstring(L"hello range")) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
