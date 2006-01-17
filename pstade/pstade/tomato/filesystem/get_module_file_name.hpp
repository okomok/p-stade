#pragma once

#include "../string/scoped_c_str_buffer.hpp"
#include "./fill_module_file_name.hpp"
#include "./max_path.hpp"

namespace pstade { namespace tomato {


template< class StringT > inline
void get_module_file_name(StringT& out, HINSTANCE hInst = _Module.GetModuleInstance())
{
	scoped_c_str_buffer<StringT> buf(out, max_path::value);
	tomato::fill_module_file_name(buf, hInst);
}


} } // namespace pstade::tomato
