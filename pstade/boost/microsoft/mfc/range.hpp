#ifndef BOOST_MICROSOFT_MFC_RANGE_HPP
#define BOOST_MICROSOFT_MFC_RANGE_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/mfc/config.hpp> // MFC_HAS_LEGACY_STRING


#include <boost/microsoft/mfc/range/afx.hpp>
#include <boost/microsoft/mfc/range/coll.hpp>
#include <boost/microsoft/mfc/range/templ.hpp>

#if !defined(BOOST_MICROSOFT_MFC_HAS_LEGACY_STRING)
    #include <boost/microsoft/mfc/range/cstringt.hpp>
    #include <boost/microsoft/mfc/range/simpstr.hpp>
#endif


#endif
