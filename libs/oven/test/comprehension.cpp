#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/comprehension.hpp>
#include <pstade/unit_test.hpp>
#include "./detail/test.hpp"


#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <string>
#include <boost/mpl/assert.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/io.hpp>
#include <iostream>
#include <vector>


namespace bll = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


void pstade_unit_test()
{
    {
        int rng1[] = { 1,2,3 };
        int rng2[] = { 4,5,6,7 };
        int rng3[] = { 8,9 };

        int ans[] = {
            1*4+8, 1*4+9, 1*5+8, 1*5+9, 1*6+8, 1*6+9, 1*7+8, 1*7+9,
            2*4+8, 2*4+9, 2*5+8, 2*5+9, 2*6+8, 2*6+9, 2*7+8, 2*7+9,
            3*4+8, 3*4+9, 3*5+8, 3*5+9, 3*6+8, 3*6+9, 3*7+8, 3*7+9
        };

        test::forward_constant(
            ans,
            comprehension(
                bll::_1 * bll::_2 + bll::_3,
                always_return(true),
                always_return(rng1),
                always_return(rng2),
                always_return(rng3)
            )
        );
    }

    {
        int rng1[] = {1,2,3,4};
        int rng2[] = {3,5,7,9};

        int ans[] = {3,5,7,9,6,10,14,18,9,15,21,27,12,20,28,36};

        test::forward_constant(
            ans,
            comprehension(bll::_1 * bll::_2, always_return(true), always_return(rng1), always_return(rng2))
        );
    }

    {
        int rng1[] = {1,5,12,3,23,11,7,2,12,0,19,3,22,8,9,99};

        int ans[] = {12,23,11,12,19,22,99};

        test::forward_constant(
            ans,
            comprehension(bll::_1, bll::_1 > 10, always_return(rng1))
        );
    }

    {
        int rng1[] = {1,3,5};
        int rng2[] = {2,4,6};

        int ans[] = {3,5,7,7,9,11};

        test::forward_constant(
            ans,
            comprehension(bll::_1+bll::_2, bll::_2 > bll::_1, always_return(rng1), always_return(rng2))
        );
    }
    {// empty test
        int rngX[] = { 1,2,3 };
        std::vector<double> rngY;
        rngY.push_back(1.2), rngY.push_back(12.3);
        std::string emptyrng;

        test::emptiness(
            comprehension(
                bll::constant(122),
                always_return(true),
                always_return(emptyrng),
                always_return(rngX),
                always_return(rngY)
            )
        );
        test::emptiness(
            comprehension(
                bll::constant(122),
                always_return(true),
                always_return(rngX),
                always_return(emptyrng),
                always_return(rngY)
            )
        );
        test::emptiness(
            comprehension(
                bll::constant(122),
                always_return(true),
                always_return(rngX),
                always_return(rngY),
                always_return(emptyrng)
            )
        );
        test::emptiness(
            comprehension(
                bll::constant(122),
                bll::constant(false),
                always_return(rngX),
                always_return(rngY),
                always_return(rngY)
            )
        );
    }
}
