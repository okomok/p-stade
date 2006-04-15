#ifndef BOOST_MICROSOFT_ATL_COMCLI_FWD_HPP
#define BOOST_MICROSOFT_ATL_COMCLI_FWD_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/guiddef.hpp> // IID


namespace ATL {


template< class T, const IID *piid >
class CComQIPtr;


template< class T >
class CAdapt;


} // nemspace ATL


#endif
