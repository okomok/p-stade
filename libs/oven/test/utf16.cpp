#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/utf16_encoded.hpp>
#include <pstade/oven/utf16_decoded.hpp>
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
        std::vector<boost::uint16_t> rng = ans|copied;
        std::vector<boost::uint32_t> expected = ans|copied;

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|utf16_decoded,
            expected
        ) );

        BOOST_CHECK( oven::test_Forward_Readable(
            rng|identities(in_forward)|utf16_decoded,
            expected
        ) );
    }

    {
        std::string ans("fjioafjioasjfiojeioajfioeawnfe");
        std::vector<boost::uint16_t> expected = ans|copied;
        std::vector<boost::uint32_t> rng = ans|copied;

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|utf16_encoded,
            expected
        ) );

        BOOST_CHECK( oven::test_SinglePass_Readable(
            rng|identities(in_single_pass)|utf16_encoded,
            expected
        ) );
    }
    {
        file_range<boost::uint16_t> frng("utf16.txt");

        BOOST_CHECK( oven::equals(
            frng|utf16_decoded|utf16_encoded,
            frng
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
