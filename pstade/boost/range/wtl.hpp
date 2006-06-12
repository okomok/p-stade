#ifndef BOOST_RANGE_WTL_HPP
#define BOOST_RANGE_WTL_HPP




// Boost.Range WTL Extension
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)




// forward declarations
//


namespace WTL {


    template< class T >
    class CSimpleStack;


} // namespace WTL




// extended customizations
//


#include <boost/range/atl.hpp>
#include <atlmisc.h> // WTL::CString
#include <tchar.h>


namespace boost { namespace range_detail_microsoft {


    template< >
    struct customization< WTL::CString >
    {
        template< class X >
        struct meta
        {
            typedef TCHAR *mutable_iterator;
            typedef TCHAR const *const_iterator;
        };

        template< class Iterator, class X >
        typename mutable_<Iterator, X>::type begin(X& x)
        {
            return x.GetBuffer(0);
        }

        template< class Iterator, class X >
        Iterator begin(X const& x)
        {
            return x;
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return begin<Iterator>(x) + x.GetLength();
        }
    };


    template< class T >
    struct customization< WTL::CSimpleStack<T> > :
        customization< ATL::CSimpleArray<T> >
    { };


} } // namespace boost::range_detail_microsoft




// range customizations
//


BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    (WTL, BOOST_PP_NIL), CString
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
    boost::range_detail_microsoft::using_type_as_tag,
    (WTL, BOOST_PP_NIL), CSimpleStack, 1
)




#endif
