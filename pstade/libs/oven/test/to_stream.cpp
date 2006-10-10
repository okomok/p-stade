#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/to_stream.hpp>


#include <sstream>
#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/to_utf8_encoder.hpp>
#include <pstade/is_same.hpp>


namespace oven = pstade::oven;
using namespace oven;


std::stringstream g_ss;


void test()
{
    std::string const src("hello,to_function");

    {
        g_ss.str("");
        std::stringstream& ss = oven::adaptor_to<std::stringstream&>( oven::copy(src, oven::to_stream(g_ss)) );
        BOOST_CHECK( oven::equals(g_ss.str(), src) );
        BOOST_CHECK( pstade::is_same(ss, g_ss) );
    }
#if 0 // seems not to be able to support reference type as 'to_base' target.
    {
        std::wstring rng(L"aabbbcccdddeffg");
        std::stringstream& ss = oven::unique_copy(rng, oven::to_utf8_encoder(oven::to_stream(g_ss)))|to_base;
        BOOST_CHECK( pstade::is_same(ss, g_ss) );
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
