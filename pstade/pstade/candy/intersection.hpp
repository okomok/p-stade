#pragma once

#include <pstade/integral_cast.hpp>
#include "./detail/greater_size_type.hpp"

namespace pstade { namespace candy {


template< class Flags0, class Flags1 > inline
typename detail::greater_size<Flags0, Flags1>::type
intersection(Flags0 fs0, Flags1 fs1)
{
	// Note:
	//   standard conversion makes smaller type to int, so we must cast to avoid warning.
	
	// Workaround: ret_t must be defined for VC6.
	typedef typename detail::greater_size<Flags0, Flags1>::type ret_t;
	return pstade::integral_cast<ret_t>(fs0 & fs1);
}


} } // namespace pstade::candy
