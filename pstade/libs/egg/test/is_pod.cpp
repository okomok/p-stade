#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/is_pod.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/mpl/placeholders.hpp>


template<class X>
struct base { };


// works only on MWCW 9 and Visual C++ 8.
BOOST_MPL_ASSERT((boost::is_pod< base<int> >));
BOOST_MPL_ASSERT((boost::is_pod< base<boost::mpl::_> >));


void pstade_minimal_test()
{
}
