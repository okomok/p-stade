#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/function_output_iterator.hpp>


#include <sstream>
#include <string>
#include <boost/range.hpp>
#include <pstade/oven/regularize_iterator.hpp>
#include <pstade/oven/functions.hpp>


std::stringstream g_ss;


void to_ss(char ch)
{
    g_ss << ch;
}


void test()
{
    using namespace pstade;
    using namespace oven;
    
    std::string src("hello,function_output_iterator");
    {
        g_ss.str("");
        oven::copy(src, oven::function_outputter(to_ss));
        BOOST_CHECK( oven::equals(g_ss.str(), src) );
    }
    {
        g_ss.str("");
        oven::copy(src, oven::make_regularize_iterator(oven::function_outputter(to_ss)));
        BOOST_CHECK( oven::equals(g_ss.str(), src) );
    }
    {
        g_ss.str("");
        oven::copy(src, oven::function_outputter_regularized(to_ss));
        BOOST_CHECK( oven::equals(g_ss.str(), src) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
