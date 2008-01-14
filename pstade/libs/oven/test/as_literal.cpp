#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/as_literal.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <vector>
#include <string>
#include <boost/range.hpp>
#include <pstade/oven/jointed.hpp>
#include <pstade/oven/single.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/copied.hpp>
#include <pstade/oven/equals.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::vector<char> a = std::string("hello range")|copied;
        test::random_access_constant("hello range"|as_literal, a);
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
        BOOST_CHECK( oven::equals(as_literal("hello range"), std::string("hello range")) );
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
            std::string("hello")|jointed(single('\0'))|jointed(std::string("range"))
        ) );
    }
    {
        BOOST_CHECK(oven::equals(std::string("abcd"), std::string("abcd")|as_literal));
    }
}
