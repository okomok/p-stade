#pragma once

namespace pstade { namespace candy {


template< class Flags > inline
Flags& flip(Flags& fs)
{
	fs = ~fs;
	return fs;
}


} } // namespace pstade::candy
