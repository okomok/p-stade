#ifndef PSTADE_OVEN_DETAIL_PURE_TRAVERSAL_HPP
#define PSTADE_OVEN_DETAIL_PURE_TRAVERSAL_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Useful when you want 'facade_iterator_category'
// to recompute IteratorCategory.
// Also, 'minimum_category' needs this.


#include "./prelude.hpp"
#include <boost/iterator/iterator_categories.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Iterator >
struct pure_traversal :
    boost::detail::pure_traversal_tag<
        typename boost::iterator_traversal<Iterator>::type
    >
{ };


} } } // namespace pstade::oven::detail


#endif
