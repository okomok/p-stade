#ifndef BOOST_MICROSOFT_WTL_RANGE_CTRLW_HPP
#define BOOST_MICROSOFT_WTL_RANGE_CTRLW_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/range/detail/simple_array_tag.hpp>
#include <boost/microsoft/detail/range/customize.hpp>
#include <boost/microsoft/wtl/ctrlw_fwd.hpp>
#include <boost/microsoft/wtl/range/detail/coll_value_type.hpp>


BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
    boost::microsoft::atl::range_detail::simple_array_tag,
    (WTL, BOOST_PP_NIL), CSimpleStack, 1
)


#endif
