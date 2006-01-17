#pragma once

#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/size.hpp>
#include <pstade/overload.hpp>
#include "../diagnostic/is_valid_tchar_pointer_range.hpp"
#include "../diagnostic/verify.hpp"

namespace pstade { namespace tomato {


///////////////////////////////////////////////////////////////////////////////
// profile_query_string
//
template< class Profile > inline
bool profile_query_string(Profile& pr, LPCTSTR pszValueName, TCHAR *pOutBuf, ULONG& ulBufs)
{
	return pstade_tomato_profile_query_string(pr, pszValueName, pOutBuf, ulBufs, overload());
}


// range interface
template< class Profile, class PointerRange >
bool profile_query_string(Profile& pr, LPCTSTR pszValueName, PointerRange& buf)
{
	ATLASSERT(tomato::is_valid_tchar_pointer_range(buf));

	ULONG ulBufs = boost::size(buf);
	return tomato::profile_query_string(pr, pszValueName, boost::begin(buf), ulBufs);
}


} } // namespace pstade::tomato


///////////////////////////////////////////////////////////////////////////////
// default
//
template< class Profile > inline
bool pstade_tomato_profile_query_string(Profile& pr, LPCTSTR pszValueName, TCHAR *pOutBuf, ULONG& ulBufs, ...)
{
	return pr.pstade_tomato_profile_query_string(pszValueName, pOutBuf, ulBufs);
}
