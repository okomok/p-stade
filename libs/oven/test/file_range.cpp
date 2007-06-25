#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// work around -- execution_monitor.ipp(60) : fatal error C1021
#define _WIN32_WINNT 0x0501


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/file_range.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <iterator>
#include <string>
#include <vector>
#include <pstade/oven/algorithm.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        file_range<> frng("non-exist.file");
        test::emptiness(frng);
        BOOST_CHECK(( !frng ));
        BOOST_CHECK(( !frng.is_open() ));
        test::lightweight_copyable(frng);
    }
    {
        std::vector<char> vec;
        oven::copy(file_range<char>("data.txt"), std::back_inserter(vec));
    }
}
