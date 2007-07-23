#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
// http://praisecurseandrecurse.blogspot.com/2007/03/haskell-for-short-attention-span-run_07.html


#include <pstade/oven/unfold.hpp>
#include <pstade/minimal_test.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/expression.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/optional/optional.hpp>


namespace lambda = boost::lambda;
using namespace pstade::oven;


boost::optional<int> mod(int i)
{
    if (i == 0)
        return boost::optional<int>();

    return i % 10;
}


void pstade_minimal_test()
{
    BOOST_AUTO(digits,
        expression(unfold(163291451, &::mod, lambda::_1 / 10)) );

    int const answer[] = { 1,5,4,1,9,2,3,6,1 };
    BOOST_CHECK( equals(digits, answer) );
}
