

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/variadic.hpp>
#include "./egg_test.hpp"

#include <boost/egg/get.hpp>
#include <pstade/result_of.hpp>


#include "./using_egg.hpp"
using pstade::result_of;


template<class Args>
struct mono_second
{
    typedef typename
        result_of<X_get_c<1>(Args&)>::type
    result_type;

    result_type operator()(Args& args) const
    {
        return X_get_c<1>()(args);
    }
};

typedef variadic_poly< mono_second<boost::mpl::_> >::type T_second;
T_second const second = BOOST_EGG_VARIADIC_POLY();


void egg_test()
{
    BOOST_CHECK( 2 == second(1,2,3,4,5) );
}
