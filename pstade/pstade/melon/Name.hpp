#ifndef PSTADE_MELON_NAME_HPP
#define PSTADE_MELON_NAME_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/or.hpp>
#include <pstade/biscuit/parser/star.hpp>
#include <pstade/biscuit/parser/primitive/chseq.hpp>
#include "./Letter.hpp"
#include "./NameChar.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
	class Letter_ = default_,
	class NameChar_ = default_
>
struct Name :
	biscuit::seq<
		biscuit::or_<
			typename detail::if_default<Letter<>, Letter_>::type,
			biscuit::chseq<'_'>,
			biscuit::chseq<':'>
		>,
		biscuit::star<
			typename detail::if_default<NameChar<>, NameChar_>::type
		>
	>
{ };


} } // namespace pstade::melon


#endif
