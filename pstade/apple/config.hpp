#ifndef PSTADE_APPLE_CONFIG_HPP
#define PSTADE_APPLE_CONFIG_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


//  Copyright Daniel James 2005-2006. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] <boost/functional/detail/container_fwd.hpp>


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>


#if (defined(__GLIBCXX__) && defined(_GLIBCXX_DEBUG)) \
    || BOOST_WORKAROUND(__BORLANDC__, > 0x551) \
    || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x842)) \
    || (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION))

#define PSTADE_APPLE_STRANGE_STD_CONTAINERS

#endif


#endif
