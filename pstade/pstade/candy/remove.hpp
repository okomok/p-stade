#ifndef PSTADE_CANDY_REMOVE_HPP
#define PSTADE_CANDY_REMOVE_HPP


// PStade.Candy
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./complement.hpp"
#include "./mask.hpp"


namespace pstade { namespace candy {


template< class Flags0, class Flags1 > inline
Flags0& remove(Flags0& fs0, Flags1 fs1)
{
	return candy::mask(fs0, candy::complement(fs1));
}


} } // namespace pstade::candy


#endif
