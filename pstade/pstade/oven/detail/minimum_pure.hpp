#ifndef PSTADE_OVEN_DETAIL_MINIMUM_PURE_HPP
#define PSTADE_OVEN_DETAIL_MINIMUM_PURE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



#include <boost/mpl/placeholders.hpp> // missing from 'minimum_category.hpp'
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include "./pure_traversal.hpp"


namespace pstade { namespace oven { namespace detail {


template< class T1, class T2 >
struct minimum_pure :
    boost::detail::minimum_category<
        typename boost::detail::pure_traversal_tag<T1>::type,
        typename boost::detail::pure_traversal_tag<T2>::type
    >
{ };


} } } // namespace pstade::oven::detail


#endif
