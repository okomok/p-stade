#ifndef PSTADE_MELON_COMMENT_HPP
#define PSTADE_MELON_COMMENT_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/minus.hpp>
#include <pstade/biscuit/parser/or.hpp>
#include <pstade/biscuit/parser/primitive/chseq.hpp>
#include <pstade/biscuit/parser/seq.hpp>
#include <pstade/biscuit/parser/star.hpp>
#include "./Char.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
	class Char_ = default_
>
struct Comment :
	biscuit::seq<
		biscuit::chseq<'<','!','-','-'>,
		biscuit::star<
			biscuit::or_<
				biscuit::minus<
					typename detail::if_default<Char<>, Char_>::type,
					biscuit::chseq<'-'>
				>,
				biscuit::seq<
					biscuit::chseq<'-'>,
					biscuit::minus<
						typename detail::if_default<Char<>, Char_>::type,
						biscuit::chseq<'-'>
					>
				>
			>
		>,
		biscuit::chseq<'-','-','>'>
	>
{ };


} } // namespace pstade::melon


#endif
