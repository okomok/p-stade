#pragma once

#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"
#include "../string/scoped_c_str_buffer.hpp"
#include "./fill_module_file_name.hpp"
#include "./max_path.hpp"
#include "./path_find_extension.hpp"

namespace pstade { namespace tomato {


template< class StringT >
void build_module_file_name_extension(StringT& out, LPCTSTR pszExt, HINSTANCE hInst = _Module.GetModuleInstance())
{
	ATLASSERT(is_valid(pszExt));
	ATLASSERT(*pszExt == _T('.') && "pstade::tomato::build_module_file_name_extension - pszExt must start from dot.");

	scoped_c_str_buffer<StringT> buf(out, max_path::value);

	tomato::fill_module_file_name(buf, hInst);

	LPTSTR psz = path_find_extension(buf.begin());
	ATLASSERT(*psz != _T('\0') && "pstade::tomato::build_module_file_name_extensio - extension is not found.");

	// See: ATL7::AtlLoadTypeLib
	tomato::verify((psz - buf.begin() + lstrlen(pszExt)) <= max_path::value);

	tomato::api_verify(lstrcpy(psz, pszExt) != NULL);
}


} } // namespace pstade::tomato
