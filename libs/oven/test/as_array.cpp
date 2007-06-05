#include "./prelude.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/as_array.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <string>
#include <vector>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string src("bienaijfeioagijgeoaioo");
    std::vector<char> a(boost::begin(src), boost::end(src));
    a.push_back('\0'); // contains null.

    {
        char str[] = "bienaijfeioagijgeoaioo";
        test::random_access_constant(str|as_array, a);
    }
    {
        test::random_access_constant(as_array("bienaijfeioagijgeoaioo"), a);
    }
    {
        // non-array
        test::random_access_constant(std::string("abcd")|as_array, std::string("abcd"));
    }
}
