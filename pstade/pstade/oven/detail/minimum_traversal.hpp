#ifndef PSTADE_OVEN_DETAIL_MINIMUM_TRAVERSAL_HPP
#define PSTADE_OVEN_DETAIL_MINIMUM_TRAVERSAL_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/zip_iterator.hpp> // detail::minimum_traversal_category_in_iterator_tuple


namespace pstade { namespace oven { namespace detail {


template< class IteratorTuple >
struct minimum_traversal :
    boost::detail::minimum_traversal_category_in_iterator_tuple<IteratorTuple>
{ };


} } } // namespace pstade::oven::detail


#endif
