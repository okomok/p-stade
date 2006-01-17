#pragma once

#include <pstade/overload.hpp>

namespace pstade { namespace tomato {


///////////////////////////////////////////////////////////////////////////////
// profile_set_string
//
template< class Profile > inline
void profile_set_string(Profile& pr, LPCTSTR pszValueName, LPCTSTR pszValue)
{
	pstade_tomato_profile_set_string(pr, pszValueName, pszValue, overload());
}


} } // namespace pstade::tomato


///////////////////////////////////////////////////////////////////////////////
// default
//
template< class Profile > inline
void pstade_tomato_profile_set_string(Profile& pr, LPCTSTR pszValueName, LPCTSTR pszValue, ...)
{
	pr.pstade_tomato_profile_set_string(pszValueName, pszValue);
}
