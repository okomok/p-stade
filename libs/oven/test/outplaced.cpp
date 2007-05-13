#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/outplaced.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <list>
#include <boost/range.hpp>
#include "./core.hpp"
#include <pstade/oven/algorithm.hpp>
#include <pstade/oven/identities.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/indirected.hpp>
#include <pstade/oven/initial_values.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/ptr_container/indirect_fun.hpp>
#include <pstade/result_of_lambda.hpp>
#include <pstade/oven/algorithm.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int const sample[] = { 2,10,15,11,8,4,5,14,6,7,9,1,3,12,13 };
        std::list<int> lst = sample|copied;
        std::vector<int> expected = sample|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            lst|outplaced|indirected, 
            expected
        ) );
    }
    {
        std::list<int> lst = initial_values(6,1,3,2,5,4);
        sort(lst|outplaced|indirected);
        BOOST_CHECK( equals(lst, initial_values(1,2,3,4,5,6)) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
