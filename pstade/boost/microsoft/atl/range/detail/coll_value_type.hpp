#ifndef BOOST_MICROSOFT_ATL_RANGE_DETAIL_COLL_VALUE_TYPE_HPP
#define BOOST_MICROSOFT_ATL_RANGE_DETAIL_COLL_VALUE_TYPE_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/config.hpp> // ATL_HAS_OLD_SIMPLE_ARRAY
#include <boost/microsoft/atl/coll_fwd.hpp>
#include <boost/microsoft/atl/simpcoll_fwd.hpp>
#include <boost/microsoft/atl/base_fwd.hpp> // CAutoPtr
#include <boost/microsoft/atl/comcli_fwd.hpp> // CComQIPtr
#include <boost/microsoft/detail/range/coll_value_type_fwd.hpp>
#include <boost/microsoft/sdk/guiddef.hpp> // IID
#include <boost/mpl/identity.hpp>


namespace boost { namespace microsoft { namespace detail { namespace range {


template< class E, class ETraits >
struct coll_value< ATL::CAtlArray<E, ETraits> > :
    mpl::identity<E>
{ };


template< class E >
struct coll_value< ATL::CAutoPtrArray<E> > :
    mpl::identity< ATL::CAutoPtr<E> >
{ };


template< class I, const IID *piid >
struct coll_value< ATL::CInterfaceArray<I, piid> > :
    mpl::identity< ATL::CComQIPtr<I, piid> >
{ };


template< class E, class ETraits >
struct coll_value< ATL::CAtlList<E, ETraits> > :
    mpl::identity<E>
{ };


template< class E >
struct coll_value< ATL::CAutoPtrList<E> > :
    mpl::identity< ATL::CAutoPtr<E> >
{ };


template< class I, const IID *piid >
struct coll_value< ATL::CInterfaceList<I, piid> > :
    mpl::identity< ATL::CComQIPtr<I, piid> >
{ };


#if !defined(BOOST_MICROSOFT_ATL_HAS_OLD_CSIMPLEARRAY)

    template< class T, class TEqual >
    struct coll_value< ATL::CSimpleArray<T, TEqual> > :
        mpl::identity<T>
    { };

#else

    template< class T >
    struct coll_value< ATL::CSimpleArray<T> > :
        mpl::identity<T>
    { };

    template< class T >
    struct coll_value< ATL::CSimpleValArray<T> > :
        mpl::identity<T>
    { };

#endif


} } } } // namespace boost::microsoft::detail::range


#endif
