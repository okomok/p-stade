

// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/result_typeof.hpp>
#include "./egg_test.hpp"


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/result_of.hpp>


using pstade::egg::result_typeof;
using pstade::result_of;


struct T_plus
{
    typedef int result_type;

    result_type operator()(int i, int j) const
    {
        return i + j;
    }
};

T_plus const plus = {};

struct T_negate
{
    typedef int result_type;

    result_type operator()(int i) const
    {
        return -i;
    }
};

T_negate const negate = {};



BOOST_MPL_ASSERT((boost::is_same<result_typeof<T_plus(int, int)>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<result_typeof<T_negate(int)>::type, int>));



void egg_test()
{
}
