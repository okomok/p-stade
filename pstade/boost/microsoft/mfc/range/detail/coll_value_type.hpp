#ifndef BOOST_MICROSOFT_MFC_RANGE_DETAIL_COLL_VALUE_TYPE_HPP
#define BOOST_MICROSOFT_MFC_RANGE_DETAIL_COLL_VALUE_TYPE_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/detail/range/coll_value_type_fwd.hpp>
#include <boost/microsoft/mfc/detail/coll_fwd.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>


namespace boost { namespace microsoft { namespace detail { namespace range {


template< class T >
struct coll_value
{
private:
    typedef mpl::map<
        mpl::pair<CByteArray,    BYTE>,
        mpl::pair<CDWordArray,   DWORD>,
        mpl::pair<CObArray,      CObject *>,
        mpl::pair<CPtrArray,     void *>,
        mpl::pair<CStringArray,  CString>,
        mpl::pair<CUIntArray,    UINT>,
        mpl::pair<CWordArray,    WORD>,

        mpl::pair<CObList,       CObject *>,
        mpl::pair<CPtrList,      void *>,
        mpl::pair<CStringList,   CString>
    > coll_val_map_t;

public:
    typedef typename mpl::at<coll_val_map_t, T>::type type;
};


template< class Type, class Arg_Type >
struct coll_value< CArray<Type, Arg_Type> > :
    mpl::identity<Type>
{ };


template< class Type, class Arg_Type >
struct coll_value< CList<Type, Arg_Type> > :
    mpl::identity<Type>
{ };


} } } } // namespace boost::microsoft::detail::range


#endif
