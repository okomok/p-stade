#ifndef PSTADE_MELON_LETTER_HPP
#define PSTADE_MELON_LETTER_HPP


// PStade.Melon
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/or.hpp>
#include "./BaseChar.hpp"
#include "./Ideographic.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
	class BaseChar_ = default_,
	class Ideographic_ = default_
>
struct Letter:
	biscuit::or_<
		typename detail::if_default<BaseChar<>, BaseChar_>::type,
		typename detail::if_default<Ideographic<>, Ideographic_>::type
	>
{ };


} } // namespace pstade::melon


#endif
