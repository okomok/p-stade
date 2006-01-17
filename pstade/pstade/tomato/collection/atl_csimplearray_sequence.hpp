#pragma once

#include <atlsimpcoll.h>
#include <pstade/overload.hpp>
#include "../workaround/atl_template.hpp"


///////////////////////////////////////////////////////////////////////////////
// clear
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS > inline
void pstade_stove_clear(
	ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS >& arr,
	pstade::overload
)
{
	arr.RemoveAll();
}


///////////////////////////////////////////////////////////////////////////////
// push_back
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS > inline
void pstade_stove_push_back(
	ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS >& arr,
	const KeyT& key,
	pstade::overload
)
{
#if (_ATL_VER >= 0x700)
	arr.Add(key);
#else
	arr.Add(const_cast<KeyT&>(key));
#endif
}
