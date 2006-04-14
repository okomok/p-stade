#ifndef BOOST_MICROSOFT_DETAIL_RANGE_LEGACY_STR_TAG_HPP
#define BOOST_MICROSOFT_DETAIL_RANGE_LEGACY_STR_TAG_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/detail/range/customize_fwd.hpp>
#include <boost/microsoft/sdk/tchar.hpp>


namespace boost { namespace microsoft { namespace detail { namespace range {


    // CString 
    //
    struct legacy_string_tag { };


} } } } // namespace boost::microsoft::detail::range


namespace boost { namespace microsoft { namespace range_customize {


    template< class StringT >
    struct metafunctions<microsoft::detail::range::legacy_string_tag, StringT>
    {
        // Note: LPTSTR/LPCTSTR is not always defined in <tchar.h>
        typedef TCHAR *mutable_iterator;
        typedef const TCHAR *const_iterator;
        typedef int size_type;
    };


    template< >
    struct functions<microsoft::detail::range::legacy_string_tag>
    {
        template< class Result, class StringT >
        typename overloaded<Result, StringT>::type begin(StringT& str)
        {
            return str.GetBuffer(0);
        }

        template< class Result, class StringT >
        Result begin(const StringT& str)
        {
            return str;
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
