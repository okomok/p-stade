#ifndef PSTADE_CANDY_MASK_HPP
#define PSTADE_CANDY_MASK_HPP


// PStade.Candy
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/integral_cast.hpp>
#include "./intersection.hpp"


namespace pstade { namespace candy {


template< class Flags0, class Flags1 > inline
Flags0& mask(Flags0& fs0, Flags1 fs1)
{
	fs0 = pstade::integral(candy::intersection(fs0, fs1));
	return fs0;
}


} } // namespace pstade::candy


#endif
