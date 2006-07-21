#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_OVEN_DEBUG
#include <pstade/oven/tab_expand_range.hpp>
#include <pstade/oven/tab_unexpand_range.hpp>


#include <fstream>
#include <iterator>
#include <string>
#include <boost/range.hpp>
#include <boost/range/concepts.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/file_range.hpp>


void test()
{
    // Under vc7.1, using-directive must be here...why?
    using namespace pstade;
    using namespace oven;

    {
        typedef tab_unexpand_range< std::string > rng_t;
        boost::function_requires< boost::ForwardRangeConcept<rng_t> >();
    }

    std::string ans("TTTactor<Scpp_token::pp_include_path,TTTact_pp_include_pathS>");
    std::string src("SSSSSSSSSSSSactor<Scpp_token::pp_include_path,SSSSSSSSSSact_pp_include_pathS>");

    tab_unexpand_range<std::string> rng(src, 4);

    std::string result;
    oven::copy(rng, std::back_inserter(result));
    BOOST_CHECK( oven::equal(rng, boost::begin(ans)) );

/*
    oven::file_range<> qfile("tab_expanded.txt");
    PSTADE_ASSERT( qfile.is_open() );

    oven::file_range<> afile("tab_unexpanded.txt");
    PSTADE_ASSERT( afile.is_open() );

    BOOST_CHECK( oven::equal(qfile|oven::tab_unexpanded(4), boost::begin(afile)) );
*/
/*
    oven::file_range<> sfile("tab_sample.txt");
    std::ofstream fout("tab_sample_result.txt", std::ios::binary);
    oven::copy(sfile|oven::tab_unexpanded(4), oven::outputter(fout));

 too slow
    BOOST_CHECK( oven::equal(
        qfile |
            oven::tab_unexpanded(4) |
            oven::tab_expanded(4) |
            oven::tab_unexpanded(4) |
            oven::tab_expanded(4),
        boost::begin(qfile))
    );
*/
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
