#ifndef BOOST_MICROSOFT_MFC_RANGE_AFX_HPP
#define BOOST_MICROSOFT_MFC_RANGE_AFX_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/mfc/config.hpp> // MFC_HAS_LEGACY_STRING


#if defined(BOOST_MICROSOFT_MFC_HAS_LEGACY_STRING)

    #include <afx.h> // CString
    #include <boost/microsoft/detail/range/customize.hpp>
    #include <boost/microsoft/detail/range/legacy_str_tag.hpp>

    BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE(
        boost::microsoft::detail::range::legacy_string_tag,
        BOOST_PP_NIL, CString
    )

#endif


#endif
