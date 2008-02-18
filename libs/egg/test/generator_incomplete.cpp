

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/generator.hpp>
#include "./egg_test.hpp"


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/egg/result_of.hpp>


#include "./using_egg.hpp"


template<class T>
struct klass;

typedef generator< klass< deduce<boost::mpl::_1, as_value> > >::type T_make_klass;
BOOST_MPL_ASSERT((boost::is_same< boost::egg::result_of_<T_make_klass(int&)>::type, klass<int> >));


void egg_test()
{
}
