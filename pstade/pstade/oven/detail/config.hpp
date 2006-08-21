#ifndef PSTADE_OVEN_DETAIL_CONFIG_HPP
#define PSTADE_OVEN_DETAIL_CONFIG_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator.hpp>
#if !defined(BOOST_RANGE_MUTABLE_ITERATOR_HPP)
    #define PSTADE_OVEN_BOOST_RANGE_VERSION_1
#endif


#if !defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    #define PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR range_mutable_iterator
    #define PSTADE_OVEN_BOOST_RANGE_BEGIN            range_begin
    #define PSTADE_OVEN_BOOST_RANGE_END              range_end
#else
    #define PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR range_iterator
    #define PSTADE_OVEN_BOOST_RANGE_BEGIN            boost_range_begin
    #define PSTADE_OVEN_BOOST_RANGE_END              boost_range_end
#endif


#if !defined(PSTADE_OVEN_RANGE_ADAPTOR_MAX_ARITY)
    #define PSTADE_OVEN_RANGE_ADAPTOR_MAX_ARITY 3
#endif


#if !defined(PSTADE_OVEN_DEBUG)
    #define PSTADE_OVEN_DEBUG_SPACE_CH ' '
    #define PSTADE_OVEN_DEBUG_TAB_CH '\t'
#else
    #define PSTADE_OVEN_DEBUG_SPACE_CH 'S'
    #define PSTADE_OVEN_DEBUG_TAB_CH 'T'
#endif


#endif
