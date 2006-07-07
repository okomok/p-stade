#ifndef PSTADE_OVEN_TRAVERSAL_TYPE_HPP
#define PSTADE_OVEN_TRAVERSAL_TYPE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp> // iterator_traversal
#include <boost/range/result_iterator.hpp>
#include <pstade/remove_rcv.hpp>


namespace pstade { namespace oven {


template< class Range >
struct traversal :
    boost::iterator_traversal<
        typename boost::range_result_iterator<
            typename remove_rcv<Range>::type
        >::type
    >
{ };


} } // namespace pstade::oven


#endif
