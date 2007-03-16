#ifndef PSTADE_OVEN_DETAIL_IS_RANDOM_ACCESS_HPP
#define PSTADE_OVEN_DETAIL_IS_RANDOM_ACCESS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A non-RandomAccessRange may be too long to diagnose.
// See "../advanced.hpp".


#include <boost/iterator/iterator_categories.hpp>
#include "../range_traversal.hpp"


namespace pstade { namespace oven { namespace detail {


inline
bool is_random_access_aux(boost::random_access_traversal_tag)
{
    return true;
}

inline
bool is_random_access_aux(boost::single_pass_traversal_tag)
{
    return false;
}


template< class Range > inline
bool is_random_access(Range const&)
{
    return detail::is_random_access_aux(typename range_traversal<Range>::type());
}


} } } // namespace pstade::oven::detail


#endif
