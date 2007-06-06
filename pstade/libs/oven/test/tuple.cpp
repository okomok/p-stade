#include "./prelude.hpp"
#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/v1_tests.hpp"
#include <pstade/oven/tuple.hpp>


#include <string>
#include <pstade/to_ref.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string src("abcdefghijklmn");
        std::vector<char> expected = src|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            boost::tuples::make_tuple(src.begin(), src.end())|pstade::to_ref,
            expected
        ) );

        typedef std::string::iterator iter_t;
        boost::tuples::cons<iter_t, boost::tuples::cons<iter_t, boost::tuples::null_type> > rng(src.begin(), src.end());
        BOOST_CHECK( oven::test_RandomAccess_Readable(
            rng|pstade::to_ref,
            expected
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
