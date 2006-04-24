#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <pstade/oven/transform_range.hpp>


#include <boost/utility/result_of.hpp>
#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/equal.hpp>
#include <functional>


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
    using namespace pstade;
    using namespace oven;

    int src[] = { 1, 2, 3, 4, 5 };
    int ans1[] = { 2, 4, 6, 8, 10 };

    {
        BOOST_CHECK((
            oven::equal( oven::make_transform_range(src, multiply2()), ans1)
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
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
