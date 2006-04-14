#ifndef BOOST_MICROSOFT_MFC_RANGE_DETAIL_ARRAY_TAG_HPP
#define BOOST_MICROSOFT_MFC_RANGE_DETAIL_ARRAY_TAG_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <afxcoll.h> // INT_PTR
#include <boost/microsoft/detail/range/array_functions.hpp>
#include <boost/microsoft/detail/range/customize_fwd.hpp>


namespace boost { namespace microsoft { namespace mfc { namespace range_detail {


    // CArray/CByteArray/CDWordArray/CStringArray/CUIntArray/CWordArray
    //
    struct array_tag { };


} } } } // namespace boost::microsoft::mfc::range_detail


namespace boost { namespace microsoft { namespace range_customize {


    template< class ArrayT >
    struct metafunctions<microsoft::mfc::range_detail::array_tag, ArrayT> :
        microsoft::detail::range::array_metafunctions<ArrayT, INT_PTR>
    { };


    template< >
    struct functions<microsoft::mfc::range_detail::array_tag> :
        microsoft::detail::range::array_functions
    { };


} } } // namespace boost::microsoft::range_customize


#endif
