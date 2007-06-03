#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/as_c_str.hpp>
#include <pstade/minimal_test.hpp>
#include <pstade/oven/test/test.hpp>


#include <string>
#include <pstade/oven/equals.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        boost::result_of<op_as_c_str(char const*)>::type rng = as_c_str("hello\0range");
        test::random_access_constant(rng, std::string("hello"));
        BOOST_CHECK( !contains_zero(rng) );
    }
    {
        BOOST_CHECK( oven::equals("hello\0range"|as_c_str, std::string("hello")) );
    }
    {
        wchar_t const *psz = L"hello range";
        BOOST_CHECK( oven::equals(psz|as_c_str, std::wstring(L"hello range")) );
        BOOST_CHECK( !contains_zero(psz|as_c_str) );
    }
    {
        wchar_t const *psz = L"hello range";
        BOOST_CHECK( oven::equals(as_c_str(psz), std::wstring(L"hello range")) );
        BOOST_CHECK( !contains_zero(as_c_str(psz)) );
    }
    {
        std::string src("hello range");
        BOOST_CHECK( oven::equals(src.c_str()|as_c_str, src) );
        BOOST_CHECK( oven::equals(src|as_c_str, src) ); // as is.
    }

    {
        std::string src("hello");
        std::vector<char> rng(boost::begin(src), boost::end(src));
        rng.push_back('\0');
        rng.push_back('r');        
        rng.push_back('n');
        rng.push_back('g');
        BOOST_CHECK( oven::equals(rng|as_c_str, std::string("hello")) );
    }
}
