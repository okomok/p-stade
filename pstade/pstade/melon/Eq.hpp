#ifndef PSTADE_MELON_EQ_HPP
#define PSTADE_MELON_EQ_HPP


// PStade.Melon
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/opt.hpp>
#include <pstade/biscuit/parser/primitive/chseq.hpp>
#include <pstade/biscuit/parser/seq.hpp>
#include "./S.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
	class S_ = default_
>
struct Eq :
	biscuit::seq<
		biscuit::opt<typename detail::if_default<S<>, S_>::type>,
		biscuit::chseq<'='>,
		biscuit::opt<typename detail::if_default<S<>, S_>::type>
	>
{ };


} } // namespace pstade::melon


#endif
