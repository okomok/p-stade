#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_CONCEPT_CHECK
#include <string>
#include <iostream>
#include <pstade/lexical_cast.hpp>
#include <pstade/oven.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>

using boost::assign::list_of;
using boost::lambda::_1;
using namespace pstade::oven;

typedef
    any_range<int, boost::single_pass_traversal_tag, int>
range;

range denominators(int x)
{
    return counting(1, x+1)|filtered(x % _1 == 0)|regularized;
}

bool is_prime(int x)
{
    return equals(denominators(x), list_of(1)(x));
}

range primes =
    iteration(1, _1 + 1)|regularized|filtered(&is_prime);

pstade::op_lexical_cast<std::string> to_string;

int main()
{
    BOOST_FOREACH (std::string p, primes|taken(500)|transformed(to_string))
        std::cout << p << ',';
}
