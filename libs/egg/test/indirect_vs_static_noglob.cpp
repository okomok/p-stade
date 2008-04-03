

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/indirect.hpp>
#include <boost/egg/static.hpp>
#include <boost/egg/fuse.hpp>
#include <boost/egg/unfuse.hpp>
#include "./egg_test.hpp"


#include "./using_egg.hpp"


struct T_plus
{
    typedef int result_type;

    result_type operator()(int i, int j) const
    {
        return i + j;
    }
};

T_plus const plus = {};


result_of_indirect<T_plus const *>::type const i_plus = BOOST_EGG_INDIRECT(&plus);
static_< boost::mpl::always<T_plus> >::type const s_plus = BOOST_EGG_STATIC();
result_of_unfuse<result_of_fuse<T_plus>::type>::type const f_plus = BOOST_EGG_UNFUSE_L BOOST_EGG_FUSE({}) BOOST_EGG_UNFUSE_R;


void egg_test()
{
    {
        volatile int i = 8, j = 9;
        i = plus(i, j);
    }
    {
        volatile int i = 8, j = 9;
        // msvc-9: the same code generated as plus.
        // gcc-3.4 : the same code generated as plus.
        // gcc-4.1: the same code generated as plus.
        i = i_plus(i, j);
    }
    {
        volatile int i = 8, j = 9;
        // msvc-9: inlined: 25 instructions.
        // gcc-3.4: inlined: 12 instructions.
        // gcc-4.1: the same code generated as plus, cool.
        i = s_plus(i, j);
    }
    {
        volatile int i = 8, j = 9;
        // msvc-9: inlined: 8 instructions.
        // gcc-3.4: inlined: 14 instructions.
        // gcc-4.1: the same code generated as plus, cool.
        i = f_plus(i, j);
    }
    {
        volatile int i = 8, j = 9;
        // msvc-9: inlined 36 instructions.
        // gcc-3.4: inlined 12 instrutions.
        // gcc-4.1: the same code generated as plus, cool.
        i = unfuse(fuse(plus))(i, j);
    }
    {
        volatile int i = 8, j = 9;
        i = plus(i, j);
    }
}
