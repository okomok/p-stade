#ifndef PSTADE_OVEN_DETAIL_IS_LEFT_TO_HPP
#define PSTADE_OVEN_DETAIL_IS_LEFT_TO_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Iterator, class Iterator_ > inline
typename range_difference<Range>::type
is_left_to_aux(Iterator const& it, Iterator_ const& it_, boost::random_access_traversal_tag)
{
    return (it_ - it) > 0;
}


template< class Iterator, class Iterator_ > inline
bool is_left_to(Iterator const& it, Iterator_ const& it_)
{
    typedef typename boost::iterator_traversal<Iterator>::type trv_t;
    return detail::is_left_to_aux(it, it_, trv_t());
}


} } } // namespace pstade::oven::detail


#endif
