#ifndef BOOST_MICROSOFT_ATL_RANGE_DETAIL_ARRAY_TAG_HPP
#define BOOST_MICROSOFT_ATL_RANGE_DETAIL_ARRAY_TAG_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/microsoft/detail/range/array_functions.hpp>
#include <boost/microsoft/detail/range/customize_fwd.hpp>


namespace boost { namespace microsoft { namespace atl { namespace range_detail {


    // CAtlArray/CAutoPtrArray/CInterfaceArray
    //
    struct array_tag { };


} } } } // namespace boost::microsoft::atl::range_detail


namespace boost { namespace microsoft { namespace range_customize {


    template< class ArrayT >
    struct metafunctions<microsoft::atl::range_detail::array_tag, ArrayT> :
        microsoft::detail::range::array_metafunctions<ArrayT, std::size_t>
    { };


    // 'GetSize' missing
    template< >
    struct functions<microsoft::atl::range_detail::array_tag>
    {
        template< class Result, class ArrayT >
        Result begin(ArrayT& arr)
        {
            return arr.GetData();
        }

        template< class Result, class ArrayT >
        Result end(ArrayT& arr)
        {
            return arr.GetData() + arr.GetCount();
        }

        template< class Result, class ArrayT >
        Result size(ArrayT& arr)
        {
            return arr.GetCount();
        }
    };


} } } // namespace boost::microsoft::range_customize


#endif
