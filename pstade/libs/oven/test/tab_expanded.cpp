#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_OVEN_DEBUG
#include <pstade/oven/tests.hpp>
#include <pstade/oven/tab_expanded.hpp>


#include <fstream>
#include <iterator>
#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/file_range.hpp>


void test()
{
    // Under vc7.1, using-directive must be here...why?
    namespace oven = pstade::oven;
    using namespace oven;

    std::string src("TABCTDEFTTGHITJ");
    std::string ans("SSSSABCSDEFSSSSSGHISJ");

    BOOST_CHECK( oven::equals(src|tab_expanded(4), ans) );

/*
    oven::file_range<> qfile("tab_unexpanded.txt");
    BOOST_CHECK( qfile.is_open() );

    oven::file_range<> afile("tab_expanded.txt");
    BOOST_CHECK( afile.is_open() );

    BOOST_CHECK( oven::equal(qfile|oven::tab_expanded(4), boost::begin(afile)) );

    pstade::print("...pass file-comparison");
*/
/*
    std::ofstream fout("tab_expand_range_dst__.txt", std::ios::binary);
    oven::copy(qfile|oven::tab_expanded(4), oven::outputter(fout));
*/
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
