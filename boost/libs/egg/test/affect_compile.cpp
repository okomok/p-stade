

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/affect.hpp>
#include "./egg_test.hpp"


#include <string>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


using namespace boost::egg::details;


// const
BOOST_MPL_ASSERT(( boost::is_same<
    affect_const<int const volatile&, double>::type,
    double
> )); // reference is not const.

BOOST_MPL_ASSERT(( boost::is_same<
    affect_const<int const volatile, double>::type,
    double const 
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect_const<int const volatile, double&>::type,
    double&
> )); // never affect to reference.

BOOST_MPL_ASSERT(( boost::is_same<
    affect_const<int const, double>::type,
    double const
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect_const<int volatile, double>::type,
    double
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect_const<int, double>::type,
    double
> ));


// volatile
BOOST_MPL_ASSERT(( boost::is_same<
    affect_volatile<int const volatile&, double>::type,
    double
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect_volatile<int const volatile, double>::type,
    double volatile 
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect_volatile<int const volatile, double&>::type,
    double&
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect_volatile<int const, double>::type,
    double
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect_volatile<int volatile, double>::type,
    double volatile
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect_volatile<int, double>::type,
    double
> ));



// cv
BOOST_MPL_ASSERT(( boost::is_same<
    affect_cv<int const volatile&, double>::type,
    double
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect_cv<int const volatile, double>::type,
    double const volatile 
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect_cv<int const volatile, double&>::type,
    double& 
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect_cv<int const, double>::type,
    double const
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect_cv<int volatile, double>::type,
    double volatile
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect_cv<int, double>::type,
    double
> ));


// all
BOOST_MPL_ASSERT(( boost::is_same<
    affect<int const volatile&, double>::type,
    double const volatile&
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect<int const volatile, double>::type,
    double const volatile
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect<int const, double>::type,
    double const
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect<int volatile, double>::type,
    double volatile
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect<int, double>::type,
    double
> ));


// no affects

BOOST_MPL_ASSERT(( boost::is_same<
    affect<int const volatile&, double&>::type,
    double&
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect<int const volatile, double&>::type,
    double&
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect<int const, double&>::type,
    double&
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect<int volatile, double&>::type,
    double&
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    affect<int, double&>::type,
    double&
> ));


void egg_test()
{ }
