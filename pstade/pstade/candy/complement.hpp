#pragma once

namespace pstade { namespace candy {


template< class Flags > inline
Flags complement(Flags fs)
{
	// See: candy::intersection

	// Note: you cannot use integral_cast.
	return static_cast<Flags>(~fs);
}


} } // namespace pstade::candy
