#ifndef BOOST_MICROSOFT_MFC_RANGE_COLL_HPP
#define BOOST_MICROSOFT_MFC_RANGE_COLL_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <afxcoll.h> // CXXXArray/List
#include <boost/microsoft/detail/range/customize.hpp>
#include <boost/microsoft/mfc/detail/coll_fwd.hpp>
#include <boost/microsoft/mfc/range/detail/array_tag.hpp>
#include <boost/microsoft/mfc/range/detail/coll_value_type.hpp>
#include <boost/microsoft/mfc/range/detail/list_tag.hpp>
#include <boost/microsoft/mfc/range/detail/ptr_array_tag.hpp>


BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE(
    boost::microsoft::mfc::range_detail::array_tag,
    BOOST_PP_NIL, CByteArray
)

BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE(
    boost::microsoft::mfc::range_detail::array_tag,
    BOOST_PP_NIL, CDWordArray
)

BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE(
    boost::microsoft::mfc::range_detail::array_tag,
    BOOST_PP_NIL, CStringArray
)


BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE(
    boost::microsoft::mfc::range_detail::array_tag,
    BOOST_PP_NIL, CUIntArray
)

BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE(
    boost::microsoft::mfc::range_detail::array_tag,
    BOOST_PP_NIL, CWordArray
)


BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE(
    boost::microsoft::mfc::range_detail::list_tag,
    BOOST_PP_NIL, CObList
)

BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE(
    boost::microsoft::mfc::range_detail::list_tag,
    BOOST_PP_NIL, CPtrList
)

BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE(
    boost::microsoft::mfc::range_detail::list_tag,
    BOOST_PP_NIL, CStringList
)


BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE(
    boost::microsoft::mfc::range_detail::ptr_array_tag,
    BOOST_PP_NIL, CObArray
)

BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE(
    boost::microsoft::mfc::range_detail::ptr_array_tag,
    BOOST_PP_NIL, CPtrArray
)


#endif
