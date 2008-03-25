

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// error message check.


#include <boost/egg/generator.hpp>
#include "./egg_test.hpp"


#include <boost/egg/const.hpp>
#include <memory>


#include "./using_egg.hpp"
namespace mpl = boost::mpl;


typedef
    generator<
        std::pair< deduce<mpl::_1, as_value>, deduce<mpl::_2, as_value> >
    >::type
T_make_pair;

BOOST_EGG_CONST((T_make_pair), make_pair) = {{}};


void egg_test()
{
    make_pair(1);
}
