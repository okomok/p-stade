#include <pstade/vodka/drink.hpp>
#include <pstade/minimal_test.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_CONCEPT_CHECK
#include <string>
#include <boost/foreach.hpp>
#include <pstade/oven/lines.hpp>
#include <pstade/oven/transformed.hpp>
#include <pstade/oven/copied.hpp>
#include <pstade/oven/converted.hpp>
#include <pstade/oven/sub_range.hpp>


#include <pstade/oven/alias.hpp>
using namespace oven;


void pstade_minimal_test()
{
    // This works, because:
    // 'lines' returns a range whose referent is a reference type.
    // Hence, make_copied works as long as lines iterator is alive
    // , where Boost.Foreach supports iterators such that 24.1/9.
    std::string text("abcd\nefg\n\nhijlkmno\npqrst\nuvwxyz\n");
    BOOST_FOREACH (std::string line, text|lines|transformed(make_copied)) {
        std::cout << line << std::endl;
    }

    // This has no pitfalls.
    BOOST_FOREACH (std::string line, text|lines|transformed(op_copy_range<std::string>())) {
        std::cout << line << std::endl;
    }

    // This seems better?
    BOOST_FOREACH (sub_range<std::string> line_, text|lines) {
        std::string line = line_|copied;
        std::cout << line << std::endl;
    }
}
