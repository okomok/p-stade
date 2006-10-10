#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/sort_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/reverse_range.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int rng[] = {5,6,4,7,8,9,1,3,2};
        int ans[] = {1,2,3,4,5,6,7,8,9};
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|sorted,
            expected
        ) );
    }

    std::string src("15423");
    const std::string csrc("23154");

    std::string ans("12345");
    
    sort_range<std::string> srng(src);
    BOOST_FOREACH (char& ch, srng) {
        std::cout << ch;
    }
    std::cout << '\n';


    BOOST_CHECK( oven::equals( srng, ans) );
    BOOST_CHECK( oven::equals( csrc|sorted, ans) );

    BOOST_CHECK( oven::equals( src|sorted, ans) );
    
    BOOST_FOREACH (char& ch, src|sorted) {
        ch += 1;
    }

    BOOST_CHECK( oven::equals( src, std::string("26534") ) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
