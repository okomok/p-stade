#include "./prefix.hpp"

// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Hmm, compiler is smart enough to detect "reference to temporary".
// is_returnable seems obsolete.


#include <pstade/oven/any_indexed.hpp>
#include <pstade/oven/any_range.hpp>
#include <pstade/oven/jointed.hpp>
#include <pstade/oven/merged.hpp>

#include <pstade/minimal_test.hpp>

#include <string>
#include <pstade/oven/rvalues.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string const str1("123456");
    std::string const str2("123456");
    {
        any_range<char const&, boost::random_access_traversal_tag> a(str1|rvalues);
        *boost::begin(a);
    }
    {
        any_indexed<char const&, boost::random_access_traversal_tag> a(str1|rvalues);
        *boost::begin(a);
    }
    {
        *boost::begin(str1|jointed(str2|rvalues));
    }
    {
        *boost::begin(str1|merged(str2|rvalues));
    }
}
