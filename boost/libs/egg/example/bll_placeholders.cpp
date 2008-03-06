

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/bll/placeholders.hpp>
#include <boost/egg/lazy.hpp>
#include <boost/egg/result_of.hpp>
#include <functional> // plus


#include "./using_bll.hpp"
#include "./egg_example.hpp"


//[code_example_bll_placeholders
void egg_example()
{
    std::plus<int> plus;

    result_of_<
        result_of_<T_lazy(std::plus<int> &)>::type(T_bll_1 const &, int)
    >::type
        f = lazy(plus)(bll_1, 10);

    int _2_ = 2;
    BOOST_CHECK( f(_2_) == 12 );
}
//]
