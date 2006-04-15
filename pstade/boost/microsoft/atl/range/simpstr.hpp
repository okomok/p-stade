#ifndef BOOST_MICROSOFT_ATL_RANGE_SIMPSTR_HPP
#define BOOST_MICROSOFT_ATL_RANGE_SIMPSTR_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/config.hpp> // ATL_HAS_OLD_SIMPLE_STRING
#include <boost/microsoft/atl/simpstr_fwd.hpp> // CSimpleStringT, CStaticString
#include <boost/microsoft/atl/range/detail/string_tag.hpp>
#include <boost/microsoft/detail/range/customize.hpp>


namespace boost { namespace microsoft { namespace atl { namespace range_detail {

    // CStaticString
    //
    struct static_string_tag { };


} } } } // namespace boost::microsoft::atl::range_detail


namespace boost { namespace microsoft { namespace range_customize {


    template< class BaseType, const int t_nSize >
    struct metafunctions<microsoft::atl::range_detail::static_string_tag, ATL::CStaticString<BaseType, t_nSize> >
    {
        typedef const BaseType *mutable_iterator;
        typedef mutable_iterator const_iterator;
        typedef int size_type;
    };


    template< >
    struct functions<microsoft::atl::range_detail::static_string_tag>
    {
        template< class Result, class StringT >
        Result begin(const StringT& str)
        {
            return str;
        }

        template< class Result, class StringT >
        Result end(const StringT& str)
        {
            return begin<Result>(str) + StringT::GetLength();
        }

        template< class Result, class StringT >
        Result size(StringT& str)
        {
            (void)str; // unused
            return StringT::GetLength();
        }
    };


} } } // namespace boost::microsoft::range_customize


#if !defined(BOOST_MICROSOFT_ATL_HAS_OLD_CSIMPLESTRING)

BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
    boost::microsoft::atl::range_detail::string_tag,
    (ATL, BOOST_PP_NIL), CSimpleStringT, (class)(bool)
)

#else

BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
    boost::microsoft::atl::range_detail::string_tag,
    (ATL, BOOST_PP_NIL), CSimpleStringT, 1
)

#endif


BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
    boost::microsoft::atl::range_detail::static_string_tag,
    (ATL, BOOST_PP_NIL), CStaticString, (class)(const int)
)


#endif
