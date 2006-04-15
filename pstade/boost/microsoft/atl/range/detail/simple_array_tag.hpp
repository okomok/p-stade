#ifndef BOOST_MICROSOFT_ATL_RANGE_DETAIL_SIMPLE_ARRAY_TAG_HPP
#define BOOST_MICROSOFT_ATL_RANGE_DETAIL_SIMPLE_ARRAY_TAG_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/detail/range/array_functions.hpp>
#include <boost/microsoft/detail/range/customize_fwd.hpp>


namespace boost { namespace microsoft { namespace atl { namespace range_detail {


// CSimpleArray/CSimpleValArray
//
struct simple_array_tag { };


} } } } // namespace boost::microsoft::atl::range_detail


namespace boost { namespace microsoft { namespace range_customize {


template< class ArrayT >
struct metafunctions<microsoft::atl::range_detail::simple_array_tag, ArrayT> :
    microsoft::detail::range::array_metafunctions<ArrayT, int>
{ };


template< >
struct functions<microsoft::atl::range_detail::simple_array_tag> :
    microsoft::detail::range::array_functions
{ };


} } } // namespace boost::microsoft::range_customize


#endif
