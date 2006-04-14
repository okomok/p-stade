#ifndef PSTADE_MELON_CDSTART_HPP
#define PSTADE_MELON_CDSTART_HPP


// PStade.Melon
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/primitive/chseq.hpp>


namespace pstade { namespace melon {


template<
	class = void
>
struct CDStart :
	biscuit::chseq<'<','!','[','C','D','A','T','A','['>
{ };


} } // namespace pstade::melon


#endif
