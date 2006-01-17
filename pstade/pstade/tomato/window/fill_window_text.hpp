#pragma once

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/size.hpp>
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/is_valid_tchar_pointer_range.hpp"
#include "../diagnostic/verify.hpp"

namespace pstade { namespace tomato {


template< class PointerRange > inline
int fill_window_text(HWND hWnd, PointerRange& buf)
{
	ATLASSERT(tomato::is_valid(hWnd));
	ATLASSERT(tomato::is_valid_tchar_pointer_range(buf));
	ATLASSERT(!boost::empty(buf)); // api document tells nothing

	// ::GetWindowText doesn't say whether failed or empty title.
	int len = ::GetWindowText(hWnd, boost::begin(buf), boost::size(buf));

	ATLASSERT(tomato::is_valid(boost::const_begin(buf)));

	return len;
}


} } // namespace pstade::tomato
