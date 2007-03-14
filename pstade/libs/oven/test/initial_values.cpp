#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/initial_values.hpp>


#include <vector>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/copy_range.hpp>
#include <boost/range/empty.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/unused.hpp>
#include <pstade/copy_assign.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int const ans[] = { 1,5,3,6,1,3,7,1,4,2,2 };
        std::vector<int> vec = initial_values(1,5,3,6,1,3,7,1,4,2,2);
        BOOST_CHECK( equals(vec, ans) );
    }
    {
        int const ans[11] = { 1,5,3,6,1,3,7,1,4,2,2 };
        boost::array<int, 11> vec = initial_values(1,5,3,6,1,3,7,1,4,2,2);
        BOOST_CHECK( equals(vec, ans) );
    }
    {
        int const ans[] = { 1,5,3,6,1,3,7,1,4,2,2 };
        std::vector<int> vec;
        pstade::copy_assign(vec, initial_values(1,5,3,6,1,3,7,1,4,2,2));
        BOOST_CHECK( equals(vec, ans) );
    }
    {
        int const ans[] = { 1,5,3,6,1,3,7,1,4,2,2 };
        std::vector<int> expected = ans|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable(
            initial_values(1,5,3,6,1,3,7,1,4,2,2),
            expected
        ) );
    }
    {
        std::vector<int> vec = initial_values();
        BOOST_CHECK( boost::empty(vec) );
    }
    {
        boost::result_of<op_initial_values(int,int,int)>::type result = { { 1,2,3 } };
        boost::result_of<op_initial_values()>::type nullary_result = { };
        pstade::unused(result, nullary_result);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
