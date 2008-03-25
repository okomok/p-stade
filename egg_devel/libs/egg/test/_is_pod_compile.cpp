

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/is_pod.hpp>
#include "./egg_test.hpp"


#include <boost/mpl/placeholders.hpp>


template<class X>
struct base { };


// works only on MWCW 9 and Visual C++ 8.
#if (defined(__MSL_CPP__) && (__MSL_CPP__ >= 0x8000)) \
 || (defined(BOOST_MSVC) && defined(_MSC_FULL_VER) && (_MSC_FULL_VER >=140050215))

    BOOST_MPL_ASSERT((boost::is_pod< base<int> >));
    BOOST_MPL_ASSERT((boost::is_pod< base<boost::mpl::_> >));

#endif


void egg_test()
{
}
