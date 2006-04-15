#ifndef BOOST_MICROSOFT_ATL_RANGE_DETAIL_STRING_TAG_HPP
#define BOOST_MICROSOFT_ATL_RANGE_DETAIL_STRING_TAG_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/detail/range/customize_fwd.hpp>


namespace boost { namespace microsoft { namespace atl { namespace range_detail {


    // CSimpleStringT/CStringT/CFixedStringT
    //
    struct string_tag { };


} } } } // namespace boost::microsoft::atl::range_detail


namespace boost { namespace microsoft { namespace range_customize {


    template< class StringT >
    struct metafunctions<microsoft::atl::range_detail::string_tag, StringT>
    {
        typedef typename StringT::PXSTR mutable_iterator;
        typedef typename StringT::PCXSTR const_iterator;
        typedef int size_type;
    };


    template< >
    struct functions<microsoft::atl::range_detail::string_tag>
    {
        template< class Result, class StringT >
        typename overloaded<Result, StringT>::type begin(StringT& str)
        {
            return str.GetBuffer(0);
        }

        template< class Result, class StringT >
        Result begin(const StringT& str)
        {
            return str.GetString();
        }

        template< class Result, class StringT >
        Result end(StringT& str)
        {
            return begin<Result>(str) + str.GetLength();
        }

        template< class Result, class StringT >
        Result size(StringT& str)
        {
            return str.GetLength();
        }
    };


} } } // namespace boost::microsoft::range_customize


#endif
