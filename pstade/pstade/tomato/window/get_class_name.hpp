#pragma once

#include "../diagnostic/is_valid.hpp"
#include "../string/scoped_c_str_buffer.hpp"
#include "fill_class_name.hpp"

namespace pstade { namespace tomato {


template< class StringT >
inline void get_class_name(HWND hWnd, StringT& out)
{
	ATLASSERT(is_valid(hWnd));

	scoped_c_str_buffer<StringT> buf(out, 255);
	tomato::fill_class_name(hWnd, buf);
}


} } // namespace pstade::tomato
