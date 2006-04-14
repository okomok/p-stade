#ifndef BOOST_MICROSOFT_WTL_RANGE_MISC_HPP
#define BOOST_MICROSOFT_WTL_RANGE_MISC_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/detail/range/customize.hpp>
#include <boost/microsoft/detail/range/legacy_str_tag.hpp>
#include <boost/microsoft/wtl/misc.hpp> // WTL::CString


BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE(
    boost::microsoft::detail::range::legacy_string_tag,
    (WTL, BOOST_PP_NIL), CString
)


#endif
