

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/static_down.hpp>
#include "./egg_test.hpp"


#include <boost/noncopyable.hpp>


#include "./using_egg.hpp"


struct my_base : boost::noncopyable
{
    virtual ~my_base() {}
};


#include BOOST_EGG_SUPPRESS_WARNING_BEGIN()
struct my_derived : my_base
{
};
#include BOOST_EGG_SUPPRESS_WARNING_END()


void egg_test()
{
    my_derived d;
    my_base &b = d;
    {
        my_derived &d_ = static_down(b);
        BOOST_CHECK(&d_ == &d);
    }
    {
        my_derived &d_ = b|static_down();
        BOOST_CHECK(&d_ == &d);
    }
    {
        my_derived const &d_ = static_down(b);
        BOOST_CHECK(&d_ == &d);
    }
    {
        my_derived const &d_ = b|static_down();
        BOOST_CHECK(&d_ == &d);
    }
}
