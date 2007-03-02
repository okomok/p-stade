#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <pstade/oven.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>

namespace lambda = boost::lambda;
using namespace pstade::oven;

typedef
    any_range<int, boost::single_pass_traversal_tag>
range;

range sieve(range rng)
{
    return rng|dropped(1)|filtered(regular(lambda::_1 % value_front(rng) != 0));
}

range primes( iteration(range(counting_from(2)), &::sieve)|transformed(front) );

int main()
{
    std::cout << (primes|taken(200));
}
