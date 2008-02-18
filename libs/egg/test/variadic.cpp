

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/variadic.hpp>
#include "./egg_test.hpp"

#include <boost/egg/get.hpp>
#include <boost/egg/result_of.hpp>


#include "./using_egg.hpp"
using boost::egg::result_of;


struct little_second
{
    template<class Me, class Args>
    struct apply :
        result_of<X_get_c<1>(Args&)>
    { };

    template<class Re, class Args>
    Re call(Args& args) const
    {
        return X_get_c<1>()(args);
    }
};

typedef variadic< little_second >::type T_second;
T_second const second = BOOST_EGG_VARIADIC({});


void egg_test()
{
    BOOST_CHECK( 2 == second(1,2,3,4,5) );
}
