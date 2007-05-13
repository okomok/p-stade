#ifndef PSTADE_OVEN_RANGE_ITERATOR_HPP
#define PSTADE_OVEN_RANGE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator.hpp>
#include <boost/range/result_iterator.hpp>
#include "./detail/config.hpp" // PSTADE_OVEN_BOOST_RANGE_VERSION_1


namespace pstade { namespace oven {


template< class Range >
struct range_iterator :
#if !defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    boost::range_iterator<Range>
#else
    boost::range_result_iterator<Range>
#endif
{ };


} } // namespace pstade::oven


#endif
