#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <pstade/oven/comprehension.hpp>
#include <pstade/oven/initial_values.hpp>
#include <pstade/oven/io.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <sstream>


namespace bll = boost::lambda;
using namespace pstade::oven;


struct make_pair
{
    typedef boost::tuple<int, int> result_type;

    result_type operator()(int i, int j) const
    {
        return result_type(i, j);
    }
};


void pstade_minimal_test()
{
    std::stringstream sout;
    sout <<
        comprehension(
            bll::bind(make_pair(), bll::_1, bll::_2), // expression
            bll::_1 < bll::_2,                        // guard
            initial_values(1,3,5),                    // -> _1
            initial_values(2,4,6)                     // -> _2
        );

    BOOST_CHECK(sout.str() == "{(1 2),(1 4),(1 6),(3 4),(3 6),(5 6)}");
}
