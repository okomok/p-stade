#pragma once

#if (_ATL_VER >= 0x0700)

#include <atlstr.h>
#include <pstade/overload.hpp>


///////////////////////////////////////////////////////////////////////////////
// clear
//
template< class BaseT, class TraitsT > inline
void pstade_stove_clear(
	ATL::CStringT<BaseT, TraitsT>& str, 
	pstade::overload
)
{
	str.Empty();
}


///////////////////////////////////////////////////////////////////////////////
// push_back
//
template< class BaseT, class TraitsT > inline
void pstade_stove_push_back(
	ATL::CStringT<BaseT, TraitsT>& str,
	typename ATL::CStringT<BaseT, TraitsT>::XCHAR ch,
	pstade::overload
)
{
	str.AppendChar(ch);
}


#endif // (_ATL_VER >= 0x0700)
