#ifndef PSTADE_OVEN_RANGE_ITERATOR_TYPE_HPP
#define PSTADE_OVEN_RANGE_ITERATOR_TYPE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include "./detail/config.hpp"


namespace pstade { namespace oven {


template< class Range >
struct range_iterator :
#if !defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    boost::range_iterator<
#else
    boost::range_result_iterator<
#endif
        typename boost::remove_reference<Range>::type
    >
{ };


} } // namespace pstade::oven


#endif
