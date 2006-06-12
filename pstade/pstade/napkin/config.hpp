#ifndef PSTADE_NAPKIN_CONFIG_HPP
#define PSTADE_NAPKIN_CONFIG_HPP


// PStade.Napkin
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>


#if defined(BOOST_NO_STRINGSTREAM) || \
    defined(BOOST_NO_STD_WSTRING) || \
    defined(BOOST_NO_STD_LOCALE)
    
    #define PSTADE_NAPKIN_NO_WIDESTRING

#endif


#endif
