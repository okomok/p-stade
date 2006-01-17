#pragma once

#include "../string/scoped_c_str_buffer.hpp"
#include "./fill_module_file_name.hpp"
#include "./max_path.hpp"
#include "./path_find_file_name.hpp"

namespace pstade { namespace tomato {


template< class StringT >
void get_module_folder_name(StringT& out, HINSTANCE hInst = _Module.GetModuleInstance())
{
	scoped_c_str_buffer<StringT> buf(out, max_path::value);

	tomato::fill_module_file_name(buf, hInst))

	LPTSTR pszExt = tomato::path_find_file_name(buf.begin());
	*pszExt = _T('\0'); // null-terminated!
}


} } // namespace pstade::tomato
