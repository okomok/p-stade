#pragma once

#include "../diagnostic/verify.hpp"
#include "../string/scoped_c_str_buffer.hpp"
#include "./get_module_folder_name.hpp"
#include "./max_path.hpp"

namespace pstade { namespace tomato {


template< class StringT >
void build_module_folder_file_name(StringT& out, LPCTSTR pszFileName, HINSTANCE hInst = _Module.GetModuleInstance())
{
	tomato::get_module_folder_name(out, hInst);

	out += pszFileName;
	tomato::verify(out.GetLength() <= max_path::value);
}


} } // namespace pstade::tomato
