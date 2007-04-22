#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/utf8_decoded.hpp>
#include <pstade/oven/utf8_encoded.hpp>

#include <string>
#include <boost/range.hpp>
#include "./core.hpp"
#include <pstade/oven/file_range.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        file_range<boost::uint8_t> frng("utf8.txt");

        BOOST_CHECK( oven::equals(
            frng|utf8_decoded|utf8_encoded,
            frng
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
