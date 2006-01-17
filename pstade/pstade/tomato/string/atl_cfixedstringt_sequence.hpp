#pragma once

#if (_ATL_VER >= 0x0700)

#include <atlstr.h>
#include <pstade/overload.hpp>


///////////////////////////////////////////////////////////////////////////////
// clear
//
template< class StringT, int chars > inline
void pstade_stove_clear(
	ATL::CFixedStringT<StringT, chars>& str,
	pstade::overload
)
{
	str.Empty();
}


///////////////////////////////////////////////////////////////////////////////
// push_back
//
template< class StringT, int chars > inline
void pstade_stove_push_back(
	ATL::CFixedStringT<StringT, chars>& str,
	typename ATL::CFixedStringT<StringT, chars>::XCHAR ch,
	pstade::overload
)
{
	str.AppendChar(ch);
}


#endif // (_ATL_VER >= 0x0700)
