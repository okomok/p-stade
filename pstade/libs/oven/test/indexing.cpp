#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/indexing.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/algorithm.hpp>


std::vector<char> g_vec;


struct vec_get
{
    typedef char result_type;

    template< class Size >
    char operator()(Size i) const
    {
        return g_vec[i];
    }
};
    

void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string ans("11111234516313!");
        oven::copy(ans, std::back_inserter(g_vec));

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            oven::indexing(0, ans.size(), vec_get()),
            g_vec
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
