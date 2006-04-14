#ifndef PSTADE_CANDY_ADD_HPP
#define PSTADE_CANDY_ADD_HPP


// PStade.Candy
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/integral_cast.hpp>
#include "./union.hpp"


namespace pstade { namespace candy {


template< class Flags0, class Flags1 > inline
Flags0& add(Flags0& fs0, Flags1 fs1)
{
	fs0 = pstade::integral(candy::union_(fs0, fs1));
	return fs0;
}


} } // namespace pstade::candy


#endif
