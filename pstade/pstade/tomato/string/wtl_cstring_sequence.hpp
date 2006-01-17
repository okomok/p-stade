#pragma once

#include <atlmisc.h>
#include <pstade/overload.hpp>


///////////////////////////////////////////////////////////////////////////////
// clear
//
inline void pstade_stove_clear(WTL::CString& str, pstade::overload)
{
	str.Empty();
}


///////////////////////////////////////////////////////////////////////////////
// push_back
//
inline void pstade_stove_push_back(WTL::CString& str, TCHAR ch, pstade::overload)
{
	str += ch;
}

