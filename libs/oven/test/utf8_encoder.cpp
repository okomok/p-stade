#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/utf8_encoder.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <vector>
#include <pstade/oven/algorithm.hpp>
#include "./detail/v1_core.hpp"
#include <pstade/oven/file_range.hpp> // VC++ does *using namespace std* here; Boost1.34 will work around this bug.
#include <pstade/oven/utf8_decoded.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;
    {
        file_range<boost::uint8_t> frng("utf8.txt");

        std::vector<boost::uint8_t> result;

        oven::copy(frng|utf8_decoded, utf8_encoder(std::back_inserter(result)));

        BOOST_CHECK( oven::equals(
            frng,
            result
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
