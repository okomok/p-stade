#ifndef PSTADE_TOMATO_ATL_COMCLI_FWD_HPP
#define PSTADE_TOMATO_ATL_COMCLI_FWD_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include "../sdk/basetyps.hpp" // IID


namespace ATL {


template< class T, const IID *piid >
class CComQIPtr;


template< class T >
class CAdapt;


} // nemspace ATL


#endif
