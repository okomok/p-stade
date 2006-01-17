#pragma once

#include <pstade/overload.hpp>

namespace pstade { namespace tomato {


///////////////////////////////////////////////////////////////////////////////
// profile_delete
//
template< class Profile > inline
void profile_delete(Profile& pr, LPCTSTR pszValueName)
{
	pstade_tomato_profile_delete(pr, pszValueName, overload());
}


} } // namespace pstade::tomato


///////////////////////////////////////////////////////////////////////////////
// default
//
template< class Profile > inline
void pstade_tomato_profile_delete(Profile& pr, LPCTSTR pszValueName, ...)
{
	pr.pstade_tomato_profile_delete(pszValueName);
}
