

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/bll/placeholders.hpp>
#include <boost/egg/bll/bind.hpp>
#include <boost/egg/result_of.hpp>
#include <functional> // plus


#include "./egg_example.hpp"


//[code_example_bll_placeholders
void egg_example()
{
    std::plus<int> plus;

    result_of_<
        T_bll_bind(std::plus<int> &, T_bll_1 const &, int)
    >::type
        f = bll_bind(plus, bll_1, 10);

    BOOST_CHECK( f(2) == 12 );
}
//]
