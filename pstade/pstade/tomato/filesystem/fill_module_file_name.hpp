#pragma once

#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/size.hpp>
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/is_valid_tchar_pointer_range.hpp"
#include "../diagnostic/verify.hpp"

namespace pstade { namespace tomato {


template< class PointerRange > inline
void fill_module_file_name(PointerRange& buf, HINSTANCE hInst = _Module.GetModuleInstance())
{
	ATLASSERT(tomato::is_valid_tchar_pointer_range(buf));
	ATLASSERT(!boost::empty(buf));

	tomato::api_verify(::GetModuleFileName(hInst, boost::begin(buf), boost::size(buf)) != 0);

	ATLASSERT(tomato::is_valid(boost::const_begin(buf)));
}


} } // namespace pstade::tomato
