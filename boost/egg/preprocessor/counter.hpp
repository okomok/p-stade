#ifndef BOOST_EGG_PREPROCESSOR_COUNTER_HPP
#define BOOST_EGG_PREPROCESSOR_COUNTER_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright Aleksey Gurtovoy 2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/boost_workaround.hpp>


#   if BOOST_WORKAROUND(BOOST_MSVC, >= 1300)
#       define BOOST_EGG_PP_COUNTER() __COUNTER__
#   else
#       define BOOST_EGG_PP_COUNTER() __LINE__
#   endif


#endif
