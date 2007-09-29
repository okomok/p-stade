#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/applier.hpp>
#include <pstade/minimal_test.hpp>


#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <boost/range/empty.hpp>
#include <pstade/oven/algorithm.hpp>
#include <pstade/oven/identities.hpp>
#include <pstade/oven/stream_writer.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/regular.hpp>
#include <pstade/unused.hpp>


std::stringstream g_ss;


void to_ss(char ch)
{
    g_ss << ch;
}


void modify(char& ch)
{
    ch = 'x';
}


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string const src("hello,applier");
    {
        g_ss.str("");
        oven::copy(src, oven::applier(&::to_ss));
        BOOST_CHECK( oven::equals(g_ss.str(), src) );
    }
    {
        g_ss.str("");
        oven::copy(src, oven::applier(regular(&::to_ss)));
        BOOST_CHECK( oven::equals(g_ss.str(), src) );
    }
    {
        std::vector<char> vec;
        oven::copy(std::string("abc"), std::back_inserter(vec));
        BOOST_CHECK( oven::equals(std::string("abc"), vec) );
        // identities keeps vec mutable.
        oven::copy(vec|identities, oven::applier(&::modify));
        BOOST_CHECK( oven::equals(std::string("xxx"), vec) );
    }
    {
        g_ss.str("");
        oven::copy(src, oven::stream_writer(g_ss));
        BOOST_CHECK( oven::equals(g_ss.str(), src) );
    }
    {
        g_ss.str("");
        oven::copy(src, oven::applier(pstade::unused));
        BOOST_CHECK( boost::empty(g_ss.str()) );
    }
}
