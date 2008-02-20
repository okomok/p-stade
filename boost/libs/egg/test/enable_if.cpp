

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/enable_if.hpp>
#include "./egg_test.hpp"


#include <boost/test/minimal.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>


using namespace boost::egg::details;


namespace temp {


    template< class T0 >
    void foo(T0,
        typename enable_if< boost::is_pointer<T0> >::type * = 0)
    {
    }

    template< class T0 >
    void foo(T0, T0)
    {
    }

}


template< class T, class = enabler >
struct bar
{
    typedef int type;
};

template< class T >
struct bar<T, typename enable_if< boost::is_pointer<T> >::type>
{
    typedef double type;
};

BOOST_MPL_ASSERT(( boost::is_same<int, bar<char>::type> ));
BOOST_MPL_ASSERT(( boost::is_same<double, bar<char *>::type> ));


void egg_test()
{
    void *p = 0;
    temp::foo(p, p);
}
