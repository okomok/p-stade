#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/transformed.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <pstade/result_of.hpp>
#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/algorithm.hpp>
#include "./detail/v1_core.hpp"
#include <functional>
#include <pstade/egg/to_value.hpp>
#include <pstade/egg/identity.hpp>
#include <pstade/egg/return.hpp>
#include <pstade/oven/regular.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>


struct multiply2 :
    std::unary_function<int, int>
{
    int operator()(int x) const { return x*2; }
};


struct div2 :
    std::unary_function<int, int>
{
    int operator()(int x) const { return x/2; }
};


int div2_(int x) { return x/2; }


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    int src[] = { 1, 2, 3, 4, 5 };
    int ans1[] = { 2, 4, 6, 8, 10 };

    {
        int rng[] = {1,2,3,4,5};
        int ans[] = {2,4,6,8,10};
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            rng|transformed(::multiply2()),
            expected
        ) );

        namespace lambda = boost::lambda;
        BOOST_CHECK( oven::test_RandomAccess_Readable(
            rng|transformed(regular(lambda::_1 * 2)),
            expected
        ) );
    }
    {
        BOOST_CHECK((
            oven::equal( oven::make_transformed(src, multiply2()), ans1)
        ));
    }

    {
        bool ok =
            oven::equal(
                src
                    | oven::transformed(multiply2())
                    | oven::transformed(div2())
                    | oven::transformed(multiply2())
                    | oven::transformed(&div2_)
                , src
            );
        
        BOOST_CHECK(ok);
    }
    {
        std::string str;
        str |
            transformed(pstade::egg::to_value) |
            // transformed(pstade::identity); // dangling!
            transformed(pstade::egg::return_< char >(pstade::egg::identity));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
