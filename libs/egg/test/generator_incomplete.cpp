#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/generator.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/egg/pstade/result_of.hpp>


namespace egg = pstade::egg;
using namespace egg;


template<class T>
struct klass;

typedef generator< klass< deduce<boost::mpl::_1, as_value> > >::type T_make_klass;
BOOST_MPL_ASSERT((boost::is_same< pstade::result_of<T_make_klass(int&)>::type, klass<int> >));


void pstade_minimal_test()
{
}
