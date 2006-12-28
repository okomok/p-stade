#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/deduced_const.hpp>


#include <boost/utility/result_of.hpp>
#include <pstade/oven/metafunctions.hpp>
#include <pstade/oven/begin_end.hpp>


namespace oven = pstade::oven;
using namespace oven;


template< class Range >
typename range_iterator<Range const>::type
algo1(Range const& rng)
{
    return begin(rng);
}

template< class Range >
typename range_iterator<PSTADE_DEDUCED_CONST(Range)>::type
algo2(Range const& rng)
{
    return begin(rng);
}

template< class Range >
typename boost::result_of<op_begin(PSTADE_DEDUCED_CONST(Range)&)>::type
algo3(Range const& rng)
{
    return begin(rng);
}


void test()
{
    int arr[] = { 1,2,3, };

    //::algo1(arr); error under VC7.1
    ::algo2(arr);
    ::algo3(arr);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
