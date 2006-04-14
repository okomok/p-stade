#ifndef PSTADE_MELON_REFERENCE_HPP
#define PSTADE_MELON_REFERENCE_HPP


// PStade.Melon
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/or.hpp>
#include "./CharRef.hpp"
#include "./EntityRef.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
	class EntityRef_ = default_,
	class CharRef_ = default_
>
struct Reference :
	biscuit::or_<
		typename detail::if_default<EntityRef<>, EntityRef_>::type,
		typename detail::if_default<CharRef<>, CharRef_>::type
	>
{ };



} } // namespace pstade::melon


#endif
