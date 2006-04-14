#ifndef PSTADE_MELON_COMBININGCHAR_HPP
#define PSTADE_MELON_COMBININGCHAR_HPP


// PStade.Melon
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/or.hpp>
#include <pstade/biscuit/parser/primitive/bchrng.hpp>
#include "./ucs4_t.hpp"


namespace pstade { namespace melon {


template<
	class = void
>
struct CombiningChar :
	biscuit::or_<
		biscuit::bchrng<ucs4_t, 0x0300, 0x0345>,
		biscuit::bchrng<ucs4_t, 0x0360, 0x0361>

		// too many
		//

	>
{ };


} } // namespace pstade::melon


#endif
