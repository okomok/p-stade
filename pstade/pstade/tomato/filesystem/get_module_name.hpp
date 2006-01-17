#pragma once

#include <algorithm>
#include <boost/range/begin.hpp>
#include "../string/scoped_c_str_buffer.hpp"
#include "./get_module_file_name.hpp"
#include "./max_path.hpp"
#include "./path_find_extension.hpp"
#include "./path_find_file_name.hpp"

namespace pstade { namespace tomato {


template< class StringT >
void get_module_name(StringT& out, HINSTANCE hInst = _Module.GetModuleInstance())
{
	StringT name;
	tomato::get_module_file_name(name, hInst);

	LPCTSTR pszFirst = tomato::path_find_file_name(boost::const_begin(name));
	ATLASSERT(pszFirst != boost::const_begin(name) && "pstade::tomato::get_module_name - file name is not found.");
	LPCTSTR pszLast = tomato::path_find_extension(pszFirst);
	ATLASSERT(*pszLast != _T('\0') && "pstade::tomato::get_module_name - extension is not found.");

	scoped_c_str_buffer<StringT> buf(out, max_path::value);
	TCHAR *ps = std::copy(pszFirst, pszLast, boost::begin(buf));
	*ps = _T('\0');
}


} } // namespace pstade::tomato
