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
#include <pstade/as.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <boost/tuple/tuple_io.hpp>


namespace assign = boost::assign;
namespace lambda = boost::lambda;
using namespace pstade::oven;


any_range<int, boost::single_pass_traversal_tag> factorials =
    counting(1, max_count) |
        scanned(1, // '1' is shared, so no dangling.
            regular(lambda::_1 * lambda::_2));


int main()
{
    std::cout << (::factorials|taken(10));
}
