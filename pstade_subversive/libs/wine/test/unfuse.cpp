#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/unfuse.hpp>


int my_plus(boost::tuples::tuple<int const&, int const&, int const&> tup)
{
    return boost::get<0>(tup) + boost::get<1>(tup) + boost::get<2>(tup);
}


int my_two(boost::tuples::tuple<>)
{
    return 2;
}


void test()
{
    using namespace pstade;

    {
        BOOST_CHECK(
            pstade::unfuse(&::my_plus)(5, 7, 2) == 14
        );
    }
    {
        BOOST_CHECK(
            pstade::unfuse(&::my_two)() == 2
        );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
