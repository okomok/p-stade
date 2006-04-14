#ifndef BOOST_MICROSOFT_MFC_RANGE_DETAIL_LIST_TAG_HPP
#define BOOST_MICROSOFT_MFC_RANGE_DETAIL_LIST_TAG_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <afxcoll.h> // INT_PTR
#include <boost/microsoft/detail/range/customize_fwd.hpp>
#include <boost/microsoft/detail/range/list_functions.hpp>


namespace boost { namespace microsoft { namespace mfc { namespace range_detail {


    // CList/CPtrList/CObList/CStringList
    //
    struct list_tag { };


} } } } // namespace boost::microsoft::mfc::range_detail


namespace boost { namespace microsoft { namespace range_customize {


    template< class ListT >
    struct metafunctions<microsoft::mfc::range_detail::list_tag, ListT> :
        microsoft::detail::range::list_metafunctions<ListT, INT_PTR>
    { };


    template< >
    struct functions<microsoft::mfc::range_detail::list_tag> :
        microsoft::detail::range::list_functions
    { };


} } } // namespace boost::microsoft::range_customize


#endif
