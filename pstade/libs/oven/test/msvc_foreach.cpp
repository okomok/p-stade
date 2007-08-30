#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>


#include <string>
#include <sstream>
#include <pstade/egg/to_string.hpp>
#include <pstade/oven/counting.hpp>
#include <pstade/oven/filtered.hpp>
#include <pstade/oven/transformed.hpp>


bool is_even(int i)
{
    return i % 2 == 0;
}


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    namespace egg = pstade::egg;
    using namespace oven;

#if BOOST_WORKAROUND(BOOST_MSVC, == 1400) // msvc-8.0

    std::stringstream sout;
    for each (std::string s in counting(0, 12)|filtered(&::is_even)|transformed(egg::to_string)) {
        sout << s;
    }
    BOOST_CHECK(sout.str() == "0246810");

    std::string s("abc");
#if 0 // doesn't compile.
    for each (char &ch in s) {
        std::cout << ch;
    }
#endif
    for each (char &ch in make_iter_range(s)) {
        ch = 'z';
    }
    BOOST_CHECK(s == "zzz");


#endif
}
