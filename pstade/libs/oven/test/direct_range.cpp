#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/direct_range.hpp>
#include <pstade/oven/indirect_range.hpp>


#include <string>
#include <pstade/oven/algorithms.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    std::string src("abcde");

    oven::direct_range<std::string> dst(src);

    BOOST_CHECK( oven::equals( dst|indirected, src ) );
    BOOST_CHECK( oven::equals( src|directed|indirected, src ) );
    BOOST_CHECK( oven::equals( src|directed|indirected|directed|indirected|directed|indirected, src ) );

}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
