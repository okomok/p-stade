

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/fuse.hpp>
#include <boost/egg/unfuse.hpp>
#include "../test/egg_test.hpp"

#include <boost/tuple/tuple.hpp>
#include <boost/fusion/include/boost_tuple.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <iostream>
#include <boost/fusion/include/for_each.hpp>


namespace bll = boost::lambda;
namespace egg = boost::egg;
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
struct fused_print
{
    typedef void result_type;

    template<class Args>
    void operator()(Args const &args) const
    {
        boost::fusion::for_each(args, std::cout << bll::_1);
    }
};

typedef result_of_unfuse<fused_print>::type T_print;
T_print const print = BOOST_EGG_UNFUSE({});

void test_unfuse()
{
    print(1, '2', "34");
}
//]


void egg_test()
{
    ::test_fuse();
    ::test_unfuse();
}
