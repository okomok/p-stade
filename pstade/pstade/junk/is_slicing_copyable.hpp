#ifndef PSTADE_OVEN_DETAIL_IS_SLICING_COPYABLE_HPP
#define PSTADE_OVEN_DETAIL_IS_SLICING_COPYABLE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/unused_to_copy.hpp>


namespace pstade {


PSTADE_HAS_XXX(pstade_oven_range_base_type)


template< class From, class Iterator >
struct is_slicing_copyable<From, oven::iter_range<Iterator>,
    typename boost::enable_if< has_pstade_oven_range_base_type<From> >::type
> :
    boost::mpl::true_
{ };


} // namespace pstade


#endif
