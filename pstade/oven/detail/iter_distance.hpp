#ifndef PSTADE_OVEN_DETAIL_ITER_DISTANCE_HPP
#define PSTADE_OVEN_DETAIL_ITER_DISTANCE_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // distance
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>


namespace pstade { namespace oven { namespace detail {


// STL regards a non-lvalue RandomAccess as InputIterator, hence hook it before.

template< class Iterator > inline
typename boost::iterator_difference<Iterator>::type
iter_distance_aux(Iterator first, Iterator last, boost::random_access_traversal_tag)
{
    return last - first;
}

template< class Iterator > inline
typename boost::iterator_difference<Iterator>::type
iter_distance_aux(Iterator first, Iterator last, boost::single_pass_traversal_tag)
{
    return std::distance(first, last);
}


template< class Iterator > inline
typename boost::iterator_difference<Iterator>::type
iter_distance(Iterator first, Iterator last)
{
    return detail::iter_distance_aux(first, last, typename boost::iterator_traversal<Iterator>::type());
}


} } } // namespace pstade::oven::detail


#endif
