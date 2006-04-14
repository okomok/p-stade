#ifndef PSTADE_MELON_ELEMENT_HPP
#define PSTADE_MELON_ELEMENT_HPP


// PStade.Melon
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/or.hpp>
#include <pstade/biscuit/parser/seq.hpp>
#include "./EmptyElemTag.hpp"
#include "./ETag.hpp"
#include "./STag.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
	class content_,
	class EmptyElemTag_ = default_,
	class STag_ = default_,
	class ETag_ = default_
>
struct element :
	biscuit::or_<
		typename detail::if_default<EmptyElemTag<>, EmptyElemTag_>::type, 
		biscuit::seq<
			typename detail::if_default<STag<>, STag_>::type,
			content_,
			typename detail::if_default<ETag<>, ETag_>::type
		>
	>
{ };


} } // namespace pstade::melon


#endif
