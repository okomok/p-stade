#pragma once

#include "./dir_separator.hpp"

namespace pstade { namespace tomato {


template< class StringT >
void add_dir_separator(StringT& str)
{
	if (
		str.IsEmpty() ||
		(str[str.GetLength() - 1] != tdir_separator::value)
	)
	{
		str += tdir_separator::value;
	}
}


} } // namespace pstade::tomato
