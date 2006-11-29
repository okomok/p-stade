#ifndef PSTADE_OVEN_RANGE_TRAVERSAL_HPP
#define PSTADE_OVEN_RANGE_TRAVERSAL_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp> // iterator_traversal
#include "./detail/pure_traversal.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template< class Range >
struct range_traversal :
    boost::iterator_traversal<
        typename range_iterator<Range>::type
    >
{ };


template< class Range >
struct range_pure_traversal :
    detail::pure_traversal<
        typename range_iterator<Range>::type
    >
{ };


} } // namespace pstade::oven


#endif
