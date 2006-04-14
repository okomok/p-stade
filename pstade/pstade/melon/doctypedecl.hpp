#ifndef PSTADE_MELON_DOCTYPEDECL_HPP
#define PSTADE_MELON_DOCTYPEDECL_HPP


// PStade.Melon
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/primitive/chseq.hpp>
#include <pstade/biscuit/parser/seq.hpp>
#include <pstade/biscuit/parser/star_until.hpp>
#include "./Char.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
	class Char_ = default_
>
struct doctypedecl :
	biscuit::seq<
		biscuit::chseq<'<','!','D','O','C','T','Y','P','E'>,
		biscuit::star_until<
			typename detail::if_default<Char<>, Char_>::type,
			biscuit::chseq<'>'>
		>
	>
{ };


} } // namespace pstade::melon


#endif
