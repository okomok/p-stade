#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_CONCEPT_CHECK
#include <pstade/oven/filterer.hpp>
#include <pstade/oven/transformer.hpp>
#include <pstade/oven/algorithm.hpp>
#include <pstade/oven/equals.hpp>
#include <vector>
#include <pstade/minimal_test.hpp>
#include <boost/lambda/core.hpp>
#include <iterator> // back_inserter
#include <boost/lambda/lambda.hpp>
#include <pstade/oven/regular.hpp>


namespace bll = boost::lambda;
using namespace pstade::oven;


void pstade_minimal_test()
{
    int const in[] = { 1,2,3,4,5,6,7,8,9,10 };
    int const answer[] = {2*3,4*3,6*3,8*3,10*3};
    std::vector<int> out;
    copy(in, filterer(regular(bll::_1 % 2 == 0)) |= transformer(regular(bll::_1 * 3)) |= std::back_inserter(out));
    BOOST_CHECK( equals(out, answer) );
}
