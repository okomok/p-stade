#ifndef PSTADE_OVEN_DIRECTORY_RANGE_HPP
#define PSTADE_OVEN_DIRECTORY_RANGE_HPP

// PStade.Oven
//
// Copyright Shunsuke Sogame and Akira Takahashi 2005-2010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

# if defined(BOOST_FILESYSTEM_VERSION) \
  && BOOST_FILESYSTEM_VERSION != 2  && BOOST_FILESYSTEM_VERSION != 3
#   error BOOST_FILESYSTEM_VERSION defined, but not as 2 or 3
# endif

# if !defined(BOOST_FILESYSTEM_VERSION)
#   define BOOST_FILESYSTEM_VERSION 2
# endif

#if BOOST_FILESYSTEM_VERSION == 2
#  include <pstade/oven/detail/directory_range_v2.hpp>

# else
#  include <pstade/oven/detail/directory_range_v3.hpp>

# endif


#endif
