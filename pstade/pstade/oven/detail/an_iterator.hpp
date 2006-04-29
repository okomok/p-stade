#ifndef PSTADE_OVEN_DETAIL_AN_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_AN_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Traversal >
struct an_iterator :
    boost::iterator_adaptor<
        an_iterator<Traversal>,
        int *,
        boost::use_default,
        Traversal
    >
{
private:
    friend class boost::iterator_core_access;
};


} } } // namespace pstade::oven::detail


#endif
