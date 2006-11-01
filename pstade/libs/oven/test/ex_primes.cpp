#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/ranges.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


typedef
    any_range<int const, boost::single_pass_traversal_tag>
any_range_;


any_range_ denominators(int x)
{
    return oven::count_from_to(1, x+1)|filtered(x % lambda::_1 == 0)|regularized;
}


bool is_prime(int x)
{
    int const youI[] = { 1, x };
    return oven::equals(denominators(x), youI);
}


any_range_ const primes =
    iteration(1, lambda::_1 + 1)|regularized|const_lvalues|filtered(&is_prime);


int main()
{
    oven::copy(primes|taken(500),
        to_ostream<int>(std::cout, ",")
    );
}
