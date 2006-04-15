#ifndef BOOST_MICROSOFT_MFC_RANGE_DETAIL_PTR_ARRAY_TAG_HPP
#define BOOST_MICROSOFT_MFC_RANGE_DETAIL_PTR_ARRAY_TAG_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <afxcoll.h> // INT_PTR
#include <boost/microsoft/detail/range/array_functions.hpp>
#include <boost/microsoft/detail/range/customize_fwd.hpp>


namespace boost { namespace microsoft { namespace mfc { namespace range_detail {


    // CArray/CByteArray/CDWordArray/CStringArray/CUIntArray/CWordArray
    //
    struct ptr_array_tag { };


} } } } // namespace boost::microsoft::mfc::range_detail


namespace boost { namespace microsoft { namespace range_customize {


    // CObArray/CPtrArray
    //
    template< >
    struct metafunctions<microsoft::mfc::range_detail::ptr_array_tag, ::CObArray>
    {
        typedef CObject **mutable_iterator;
        typedef const CObject **const_iterator;
        typedef INT_PTR size_type;
    };


    template< >
    struct metafunctions<microsoft::mfc::range_detail::ptr_array_tag, ::CPtrArray>
    {
        typedef void *mutable_iterator;
        typedef const void *const_iterator;
        typedef INT_PTR size_type;
    };


    template< >
    struct functions<microsoft::mfc::range_detail::ptr_array_tag> :
        microsoft::detail::range::array_functions
    { };


} } } // namespace boost::microsoft::range_customize


#endif
