#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/counting_range.hpp>


#include <iterator>
#include <boost/bind.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/ranges.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;

typedef any_range<int const, boost::bidirectional_traversal_tag>
any_range_;

any_range_ denominators(int x)
{
    return oven::from_1_to(x+1)|filtered(x % lambda::_1 == 0)|regularized;
}

bool is_prime(int x)
{
    return oven::equals(denominators(x), 1|as_single|appended(x));
}

any_range_ primes(int x)
{
    return oven::from_1_to(x+1)|filtered(&is_prime);
}


int test_main(int, char*[])
{
    oven::copy(primes(5000), std::ostream_iterator<int>(std::cout, ","));
    return 0;
}
