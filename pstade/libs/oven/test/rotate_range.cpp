#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/rotate_range.hpp>


#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/metafunctions.hpp>


namespace oven = pstade::oven;
using namespace oven;


struct next_3
{
    template< class Range >
    typename range_iterator<Range>::type
    operator()(Range& rng)
    {
        return boost::begin(rng) + 3;
    }
};


void test()
{
    {
        int A[]  = { 1,1,1,2,2,2,2 };
        int AA[] = { 2,2,2,2,1,1,1 };

        BOOST_CHECK( oven::equals(AA, A|rotated(next_3())) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
