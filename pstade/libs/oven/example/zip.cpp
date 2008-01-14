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
#include <pstade/oven.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <boost/tuple/tuple_io.hpp>


namespace assign = boost::assign;
namespace lambda = boost::lambda;
using namespace pstade::oven;


int main()
{
    std::cout <<
        (
            boost::make_tuple(
                assign::list_of(1)(2)(3),
                assign::list_of(2)(3)(4)
            )
                | zipped
        )
              << std::endl;

    std::cout <<
        (
            assign::list_of
                (boost::make_tuple(1,2))
                (boost::make_tuple(2,3))
                (boost::make_tuple(3,4))
                | unzipped
        )
              << std::endl;

}
