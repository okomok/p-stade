

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/poly.hpp>
#include <boost/egg/result_of.hpp>


#include "./egg_example.hpp"


//[code_example_poly
template<class F, class X>
struct mono_twice
{
    typedef typename
        result_of_<F(typename result_of_<F(X &)>::type)>::type
    result_type;

    result_type operator()(F &f, X &x) const
    {
        return f(f(x));
    }
};

typedef
    poly< mono_twice<boost::mpl::_, boost::mpl::_> >::type
T_twice;

T_twice const twice = {{}};

int increment(int i) { return i + 1; }

void egg_example()
{
    BOOST_CHECK(twice(&increment, 3) == 5);
}
//]
