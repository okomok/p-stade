#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/fuse.hpp>
#include <pstade/egg/unfuse.hpp>
#include <pstade/minimal_test.hpp>

#include <boost/tuple/tuple.hpp>

#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include <boost/fusion/include/boost_tuple.hpp>
#endif


namespace egg = pstade::egg;
using namespace egg;

//[code_fuse_example
int unfused_plus(int i, int j, int k)
{
    return i + j + k;
}

void test_fuse()
{
    BOOST_CHECK( 1+2+3 == fuse(&unfused_plus)(boost::make_tuple(1,2,3)) );
}
//]

//[code_unfuse_example
int fused_plus(boost::tuple<int, int, int> const &t)
{
    return boost::get<0>(t) + boost::get<1>(t) + boost::get<2>(t);
}

void test_unfuse()
{
    BOOST_CHECK( 1+2+3 == unfuse(&fused_plus)(1,2,3) );
}
//]


void pstade_minimal_test()
{
    ::test_fuse();
    ::test_unfuse();
}
