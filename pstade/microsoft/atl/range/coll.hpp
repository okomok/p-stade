#ifndef BOOST_MICROSOFT_ATL_RANGE_ATL_COLL_HPP
#define BOOST_MICROSOFT_ATL_RANGE_ATL_COLL_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/coll_fwd.hpp>
#include <boost/microsoft/atl/range/detail/array_tag.hpp>
#include <boost/microsoft/atl/range/detail/coll_value_type.hpp>
#include <boost/microsoft/atl/range/detail/list_tag.hpp>
#include <boost/microsoft/detail/range/customize.hpp>


BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
    boost::microsoft::atl::range_detail::array_tag,
    (ATL, BOOST_PP_NIL), CAtlArray, 2
)

BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
    boost::microsoft::atl::range_detail::array_tag,
    (ATL, BOOST_PP_NIL), CAutoPtrArray, 1
)

BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
    boost::microsoft::atl::range_detail::array_tag,
    (ATL, BOOST_PP_NIL), CInterfaceArray, (class)(const IID *)
)


BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
    boost::microsoft::atl::range_detail::list_tag,
    (ATL, BOOST_PP_NIL), CAtlList, 2
)

BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
    boost::microsoft::atl::range_detail::list_tag,
    (ATL, BOOST_PP_NIL), CAutoPtrList, 1
)

BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
    boost::microsoft::atl::range_detail::list_tag,
    (ATL, BOOST_PP_NIL), CInterfaceList, (class)(const IID *)
)


#endif
