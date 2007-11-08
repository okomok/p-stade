#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/static_down.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/noncopyable.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct my_base : boost::noncopyable
{
    virtual ~my_base() {}
};

struct my_derived : my_base
{
};


template<class X>
X const & pass_through(X const & x)
{
    return x;
}


void pstade_minimal_test()
{
    my_derived d;
    my_base &b = d;
    {
        my_derived &d_ = pass_through(static_down(b));
        BOOST_CHECK(&d_ == &d);
    }
}
