#pragma once

#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/size.hpp>
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/is_valid_tchar_pointer_range.hpp"
#include "../diagnostic/verify.hpp"

namespace pstade { namespace tomato {


template< class PointerRange > inline
void fill_class_name(HWND hWnd, PointerRange& buf)
{
	ATLASSERT(tomato::is_valid(hWnd));
	ATLASSERT(tomato::is_valid_tchar_pointer_range(buf));
	ATLASSERT(!boost::empty(buf));

	tomato::api_verify(::GetClassName(hWnd, boost::begin(buf), boost::size(buf)) != 0);

	ATLASSERT(tomato::is_valid(boost::const_begin(buf)));
}


} } // namespace pstade::tomato
