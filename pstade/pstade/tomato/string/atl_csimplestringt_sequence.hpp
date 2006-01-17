#pragma once

#if (_ATL_VER >= 0x0700)

#include <atlsimpstr.h>
#include <pstade/overload.hpp>
#include "../workaround/atl_template.hpp"


///////////////////////////////////////////////////////////////////////////////
// clear
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS > inline
void pstade_stove_clear(
	ATL::CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS >& str,
	pstade::overload
)
{
	str.Empty();
}


///////////////////////////////////////////////////////////////////////////////
// push_back
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS > inline
void pstade_stove_push_back(
	ATL::CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS >& str,
	typename ATL::CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS >::XCHAR ch,
	pstade::overload
)
{
	str.AppendChar(ch);
}


#endif // (_ATL_VER >= 0x0700)
