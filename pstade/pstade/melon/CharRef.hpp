#ifndef PSTADE_MELON_CHARREF_HPP
#define PSTADE_MELON_CHARREF_HPP


// PStade.Melon
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/or.hpp>
#include <pstade/biscuit/parser/plus.hpp>
#include <pstade/biscuit/parser/primitive/chrng.hpp>
#include <pstade/biscuit/parser/primitive/chseq.hpp>
#include <pstade/biscuit/parser/seq.hpp>
#include <pstade/biscuit/parser/star.hpp>


namespace pstade { namespace melon {


template<
	class = void
>
struct CharRef :
	biscuit::or_<
		biscuit::seq<
			biscuit::chseq<'&','#'>,
			biscuit::plus< biscuit::chrng<'0','9'> >,
			biscuit::chseq<';'>
		>,
		biscuit::seq<
			biscuit::chseq<'&','#','x'>,
			biscuit::plus<
				biscuit::or_<
					biscuit::chrng<'0','9'>,
					biscuit::chrng<'a','f'>,
					biscuit::chrng<'A','F'>
				>
			>,
			biscuit::chseq<';'>
		>
	>
{ };


} } // namespace pstade::melon


#endif
