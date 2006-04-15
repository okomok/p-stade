#ifndef BOOST_MICROSOFT_ATL_RANGE_DETAIL_LIST_TAG_HPP
#define BOOST_MICROSOFT_ATL_RANGE_DETAIL_LIST_TAG_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/detail/range/customize_fwd.hpp>
#include <boost/microsoft/detail/range/list_functions.hpp>


namespace boost { namespace microsoft { namespace atl { namespace range_detail {


    // CAtlList/CAutoPtrList/CInterfaceList
    //
    struct list_tag { };


} } } } // namespace boost::microsoft::atl::range_detail


namespace boost { namespace microsoft { namespace range_customize {


    template< class ListT >
    struct metafunctions<microsoft::atl::range_detail::list_tag, ListT> :
        microsoft::detail::range::list_metafunctions<ListT, std::size_t>
    { };


    template< >
    struct functions<microsoft::atl::range_detail::list_tag> :
        microsoft::detail::range::list_functions
    { };


} } } // namespace boost::microsoft::range_customize


#endif
