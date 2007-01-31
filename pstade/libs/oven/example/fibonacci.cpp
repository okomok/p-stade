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
#include <pstade/oven/recursion.hpp>


namespace assign = boost::assign;
namespace lambda = boost::lambda;
using namespace pstade::oven;


typedef
    any_range<int, boost::single_pass_traversal_tag>
range;


int main()
{
}
