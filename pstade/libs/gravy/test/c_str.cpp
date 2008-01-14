#include <pstade/vodka/drink.hpp>
#include <pstade/minimal_test.hpp> // include first for Win32 Boost.Test


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/c_str.hpp>


#include <pstade/gravy/tstring.hpp>


namespace gravy = pstade::gravy;
using namespace gravy;


void pstade_minimal_test()
{
    {
        tstring s("abcdefg");
        TCHAR const *psz = s.c_str();
        BOOST_CHECK(psz == c_str(s));
        BOOST_CHECK(psz == (s|c_str));
        BOOST_CHECK(psz == (s|c_str()));
    }
    {
        TCHAR const s[] = "abcdefg";
        BOOST_CHECK( c_str(s) == &s[0] );
    }
}
