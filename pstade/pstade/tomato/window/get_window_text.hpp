#pragma once

#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"
#include "../string/scoped_c_str_buffer.hpp"
#include "./fill_window_text.hpp"

namespace pstade { namespace tomato {


template< class StringT > inline
void get_window_text(HWND hWnd, StringT& out)
{
	ATLASSERT(tomato::is_valid(hWnd));

	int len = ::GetWindowTextLength(hWnd);
	scoped_c_str_buffer<StringT> buf(out, len);
	tomato::api_verify(tomato::fill_window_text(hWnd, buf) >= len);
}


} } // namespace pstade::tomato
