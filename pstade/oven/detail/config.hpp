#ifndef PSTADE_OVEN_DETAIL_CONFIG_HPP
#define PSTADE_OVEN_DETAIL_CONFIG_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_HAS_THREADS
#include <boost/range/iterator.hpp>


#if !defined(BOOST_RANGE_MUTABLE_ITERATOR_HPP)
    #define PSTADE_OVEN_BOOST_RANGE_VERSION_1
#endif


#if !defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    #define PSTADE_OVEN_BOOST_RANGE_RESULT_ITERATOR  range_iterator
    #define PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR range_mutable_iterator
    #define PSTADE_OVEN_BOOST_RANGE_BEGIN            range_begin
    #define PSTADE_OVEN_BOOST_RANGE_END              range_end
#else
    #include <boost/range/result_iterator.hpp>
    #define PSTADE_OVEN_BOOST_RANGE_RESULT_ITERATOR  range_result_iterator
    #define PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR range_iterator
    #define PSTADE_OVEN_BOOST_RANGE_BEGIN            boost_range_begin
    #define PSTADE_OVEN_BOOST_RANGE_END              boost_range_end
#endif


#if defined(BOOST_HAS_THREADS) && !defined(PSTADE_OVEN_DISABLE_THREADS)
    #define PSTADE_OVEN_HAS_THREADS
#endif


#endif
