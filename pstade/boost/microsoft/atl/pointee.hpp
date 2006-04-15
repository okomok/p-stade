#ifndef BOOST_MICROSOFT_ATL_POINTEE_HPP
#define BOOST_MICROSOFT_ATL_POINTEE_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/base_fwd.hpp> // CAutoPtr
#include <boost/microsoft/atl/comcli_fwd.hpp> // CAdapt
#include <boost/mpl/identity.hpp>
#include <boost/pointee.hpp>


namespace boost {


template< class E >
struct pointee< ::ATL::CAutoPtr<E> > :
    mpl::identity<E>
{ };


template< class T >
struct pointee< ::ATL::CAdapt<T> > :
    pointee<T>
{ };


} // namespace boost


#endif
