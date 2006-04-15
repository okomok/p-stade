#ifndef BOOST_MICROSOFT_MFC_RANGE_TEMPL_HPP
#define BOOST_MICROSOFT_MFC_RANGE_TEMPL_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/detail/range/customize.hpp>
#include <boost/microsoft/mfc/detail/coll_fwd.hpp>
#include <boost/microsoft/mfc/range/detail/coll_value_type.hpp>
#include <boost/microsoft/mfc/range/detail/array_tag.hpp>
#include <boost/microsoft/mfc/range/detail/list_tag.hpp>


BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
    boost::microsoft::mfc::range_detail::array_tag,
    BOOST_PP_NIL, CArray, 2
)


BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
    boost::microsoft::mfc::range_detail::list_tag,
    BOOST_PP_NIL, CList, 2
)


#endif
