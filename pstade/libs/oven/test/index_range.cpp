#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/index_range.hpp>


#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/reverse_range.hpp>


std::vector<char> g_vec;


struct vec_get
{
    typedef char result_type;

    char operator()(int i) const
    {
        return g_vec[i];
    }
};
    

void test()
{
    using namespace pstade;
    using namespace boost;
    using namespace oven;

    {
        std::string src("11111234516313!");
        g_vec = src|copied;

        BOOST_CHECK( oven::equals(src, oven::make_index_range(vec_get(), 0, (int)src.size())) );
        BOOST_CHECK( oven::equals(src|reversed, oven::make_index_range(vec_get(), 0, (int)src.size())|reversed) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
