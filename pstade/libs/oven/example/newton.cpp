#include <pstade/detect_result_type.hpp>
#include <pstade/unit_test.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
// http://www.cs.bham.ac.uk/~ard/modules/swh05.html


#include "../test/detail/v1_tests.hpp"


#include <iostream>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/bind.hpp>
#include <pstade/oven/iteration.hpp>
#include <pstade/oven/filtered.hpp>
#include <pstade/oven/front.hpp>
#include <pstade/oven/regular.hpp>


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


float my_abs(float x)
{
    return x >= 0 ? x : -x;
}


struct satisfactory
{
    typedef bool result_type;

    bool operator()(float x, float y) const
    {
        return my_abs(y*y - x) < 0.01;
    }
};


struct improve
{
    typedef float result_type;

    float operator()(float x, float y) const
    {
        return (y + x/y)/2;
    }
};


float root(float x)
{
    return
        iteration(1.0f, regular(lambda::bind(improve(), x, lambda::_1)))
        | filtered(regular(lambda::bind(satisfactory(), x, lambda::_1)))
        | value_front();
}


void pstade_unit_test()
{
    std::cout << root(9);
}

