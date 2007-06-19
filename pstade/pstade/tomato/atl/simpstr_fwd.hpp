#ifndef PSTADE_TOMATO_ATL_SIMPSTR_FWD_HPP
#define PSTADE_TOMATO_ATL_SIMPSTR_FWD_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include "./config.hpp" // ATL_HAS_OLD_SIMPLE_STRING


namespace ATL {


#if !defined(PSTADE_TOMATO_ATL_HAS_OLD_CSIMPLESTRING)

    template< class BaseType, bool t_bMFCDLL >
    class CSimpleStringT;

#else

    template< class BaseType >
    class CSimpleStringT;

#endif


template< class BaseType, const int t_nSize >
class CStaticString;


} // namespace ATL


#endif
