#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/next_prior.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::string src("0123456789");

        BOOST_CHECK( *oven::next_begin(src) == '1' );
        BOOST_CHECK( *oven::prior_end(src) == '9' );
        BOOST_CHECK( *(src|next_begins) == '1' );
        BOOST_CHECK( *(src|prior_ends) == '9' );

        BOOST_CHECK( *oven::next_begin(src, 3) == '3' );
        BOOST_CHECK( *oven::prior_end(src, 3) == '7' );
        BOOST_CHECK( *(src|next_begins(3)) == '3' );
        BOOST_CHECK( *(src|prior_ends(3)) == '7' );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
