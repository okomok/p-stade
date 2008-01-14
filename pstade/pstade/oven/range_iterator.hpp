#ifndef PSTADE_OVEN_RANGE_ITERATOR_HPP
#define PSTADE_OVEN_RANGE_ITERATOR_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/config.hpp"

#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    #include <boost/range/result_iterator.hpp>
#else
    #include <boost/range/iterator.hpp>
#endif


namespace pstade { namespace oven {


template< class Range >
struct range_iterator :
#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    boost::range_result_iterator<
#else
    boost::range_iterator<
#endif
        Range
    >
{ };


} } // namespace pstade::oven


#endif
