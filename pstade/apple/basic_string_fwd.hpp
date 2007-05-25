#ifndef PSTADE_APPLE_BASIC_STRING_FWD_HPP
#define PSTADE_APPLE_BASIC_STRING_FWD_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./config.hpp"


#if !defined(PSTADE_APPLE_STRANGE_STD_CONTAINERS)


namespace std {


template< class CharT, class Traits, class Alloc >
class basic_string;


} // namespace std


#else
#include <string>
#endif


#endif
