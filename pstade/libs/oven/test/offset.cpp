#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/offset.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <boost/range.hpp>
#include "./detail/v1_core.hpp"


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    int A[] = { 0,1,2,3,4,5,6,7,8,9 };
    {
        int ans[] = { 3,4,5,6,7 };
        std::vector<int> expected = ans|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            boost::make_iterator_range(A+1,A+6)|offset(2,2),
            expected
        ) );
    }
    {
        BOOST_CHECK( oven::equals(
            boost::make_iterator_range(A+1,A+4)|offset(1,1),
            boost::make_iterator_range(A+2,A+5)
        ) );
    }

    std::string rng("0123456789");
    {
        std::vector<char> expected = std::string("12345678")|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|offset(1,-1),
            expected
        ) );
    }
    {
        std::vector<char> expected = std::string("345")|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|offset(1,-1)|offset(2,-3),
            expected
        ) );
    }

    {
        std::string src("0123456789");
        {
            BOOST_CHECK( oven::equals(
                src|offset(1, -1),
                std::string("12345678")
            ) );
        }
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
