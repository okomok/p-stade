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
#include <pstade/oven/tab_expanded.hpp>
#include <pstade/oven/tab_unexpanded.hpp>


#include <fstream>
#include <iterator>
#include <string>
#include <boost/range.hpp>
#include "./detail/v1_core.hpp"
#include <pstade/oven/file_range.hpp>
#include <pstade/oven/stream_writer.hpp>
#include <pstade/oven/algorithm.hpp>


void test()
{
    // Under vc7.1, using-directive must be here...why?
    namespace oven = pstade::oven;
    using namespace oven;

    std::string ans("TTTactor<Scpp_token::pp_include_path,TTTact_pp_include_pathS>");
    std::string src("SSSSSSSSSSSSactor<Scpp_token::pp_include_path,SSSSSSSSSSact_pp_include_pathS>");

    BOOST_CHECK( oven::equals(src|tab_unexpanded(4, 'X', 'T', 'S'), ans) );

    {
        oven::file_range<> qfile("tab_expanded.txt");
        BOOST_CHECK( qfile.is_open() );

        oven::file_range<> afile("tab_unexpanded.txt");
        BOOST_CHECK( afile.is_open() );

        BOOST_CHECK( equals(qfile|oven::tab_unexpanded(4), afile) );
#if 0
        std::ofstream fout("tab_unexpanded_output.txt", std::ios::binary);
        copy(qfile|oven::tab_unexpanded(4), stream_writer(fout));
#endif
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
