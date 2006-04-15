#ifndef BOOST_MICROSOFT_ATL_RANGE_STR_HPP
#define BOOST_MICROSOFT_ATL_RANGE_STR_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/config.hpp> // ATL_HAS_OLD_SIMPLE_STRING
#include <boost/microsoft/atl/str_fwd.hpp>
#include <boost/microsoft/atl/range/detail/string_tag.hpp>
#include <boost/microsoft/detail/range/customize.hpp>


BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
    boost::microsoft::atl::range_detail::string_tag,
    (ATL, BOOST_PP_NIL), CStringT, 2
)


#endif
