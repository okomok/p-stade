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


#include <fstream>
#include <iterator>
#include <string>
#include <boost/range.hpp>
#include <boost/range/concepts.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/oven/file_range.hpp>


void test()
{
    // Under vc7.1, using-directive must be here...why?
    using namespace pstade;
    using namespace oven;

    {
        typedef tab_expand_range< std::string > rng_t;
        boost::function_requires< boost::ForwardRangeConcept<rng_t> >();
    }

    std::string src("TABCTDEFTTGHITJ");
    std::string ans("SSSSABCSDEFSSSSSGHISJ");

    tab_expand_range<std::string> rng(src, 4);

    std::string result;
    oven::copy(rng, std::back_inserter(result));
    BOOST_CHECK( oven::equals(rng, ans) );

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
