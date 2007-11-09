#ifndef PSTADE_OVEN_DETAIL_BOOST_EXTENSION_FWD_HPP
#define PSTADE_OVEN_DETAIL_BOOST_EXTENSION_FWD_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./config.hpp"


#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    #define PSTADE_OVEN_MUTABLE_ITERATOR_NAME range_iterator
    #define PSTADE_OVEN_RANGE_BEGIN_NAME      boost_range_begin
    #define PSTADE_OVEN_RANGE_END_NAME        boost_range_end
#else
    #define PSTADE_OVEN_MUTABLE_ITERATOR_NAME range_mutable_iterator
    #define PSTADE_OVEN_RANGE_BEGIN_NAME      range_begin
    #define PSTADE_OVEN_RANGE_END_NAME        range_end
#endif


namespace boost {


#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    template< class Range >
    struct range_iterator;
#else
    template< class Range >
    struct range_mutable_iterator;
#endif

    template< class Range >
    struct range_const_iterator;

    template< class Range >
    struct range_size;


} // namespace boost


#endif
