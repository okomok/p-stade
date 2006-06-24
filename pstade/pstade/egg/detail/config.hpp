#ifndef PSTADE_EGG_DETAIL_CONFIG_HPP
#define PSTADE_EGG_DETAIL_CONFIG_HPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>


#if defined(BOOST_MSVC)

    #define PSTADE_EGG_DETAIL_NO_NESTED_RESULT_SPECIALIZATION

#endif


#if !defined(PSTADE_EGG_MAX_ARITY)

    #define PSTADE_EGG_MAX_ARITY 5

#endif


#endif
