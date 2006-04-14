#ifndef PSTADE_MELON_ATTRIBUTE_HPP
#define PSTADE_MELON_ATTRIBUTE_HPP


// PStade.Melon
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/seq.hpp>
#include "./AttValue.hpp"
#include "./Eq.hpp"
#include "./Name.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
	class Name_ = default_,
	class AttValue_ = default_,
	class Eq_ = default_
>
struct Attribute :
	biscuit::seq<
		typename detail::if_default<Name<>, Name_>::type,
		typename detail::if_default<Eq<>, Eq_>::type,
		typename detail::if_default<AttValue<>, AttValue_>::type
	>
{ };


} } // namespace pstade::melon


#endif
