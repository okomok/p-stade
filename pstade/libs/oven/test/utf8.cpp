#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/utf8_encoded.hpp>
#include <pstade/oven/utf8_decoded.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <string>
#include <boost/range.hpp>
#include "./detail/v1_core.hpp"
#include <pstade/oven/file_range.hpp>
#include <pstade/oven/identities.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string ans("fjioafjioasjfiojeioajfioeawnfe");
        std::vector<boost::uint8_t> rng = ans|copied;
        std::vector<boost::uint32_t> expected = ans|copied;

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|utf8_decoded,
            expected
        ) );

        BOOST_CHECK( oven::test_Forward_Readable(
            rng|identities(in_forward)|utf8_decoded,
            expected
        ) );
    }

    {
        std::string ans("fjioafjioasjfiojeioajfioeawnfe");
        std::vector<boost::uint8_t> expected = ans|copied;
        std::vector<boost::uint32_t> rng = ans|copied;

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|utf8_encoded,
            expected
        ) );

        BOOST_CHECK( oven::test_SinglePass_Readable(
            rng|identities(in_single_pass)|utf8_encoded,
            expected
        ) );
    }
    {
        file_range<boost::uint8_t> frng("utf8.txt");
        BOOST_CHECK(frng.is_open());

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
