#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/utf16_encoder.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <vector>
#include <pstade/oven/algorithm.hpp>
#include "./detail/v1_core.hpp"
#include <pstade/oven/file_range.hpp> // VC++ does *using namespace std* here; Boost1.34 will work around this bug.
#include <pstade/oven/utf16_decoded.hpp>
#include "./detail/output_iterator.hpp"


void test_()
{
    namespace oven = pstade::oven;
    using namespace oven;
    {
        file_range<boost::uint16_t> frng("utf16.txt");
        BOOST_CHECK(frng.is_open());

        std::vector<boost::uint16_t> result;

        oven::copy(frng|utf16_decoded, utf16_encoder|=std::back_inserter(result));

        BOOST_CHECK( oven::equals(
            frng,
            result
        ) );
    }
    {
        boost::uint16_t buf[10];
        test::output_iterator( utf16_encoder |= &buf[0], boost::uint32_t('a') );
    }
}


int test_main(int, char*[])
{
    ::test_();
    return 0;
}
