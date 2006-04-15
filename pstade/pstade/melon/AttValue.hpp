#ifndef PSTADE_MELON_ATTVALUE_HPP
#define PSTADE_MELON_ATTVALUE_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/not.hpp>
#include <pstade/biscuit/parser/or.hpp>
#include <pstade/biscuit/parser/primitive/chseq.hpp>
#include <pstade/biscuit/parser/primitive/chset.hpp>
#include <pstade/biscuit/parser/seq.hpp>
#include <pstade/biscuit/parser/star.hpp>
#include "./Reference.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
	class Reference_ = default_
>
struct AttValue :
	biscuit::or_<
		biscuit::seq<
			biscuit::chseq<'"'>,
			biscuit::star<
				biscuit::or_<
					biscuit::not_< biscuit::chset<'<','&','"'> >,
					typename detail::if_default<Reference<>, Reference_>::type
				>
			>,
			biscuit::chseq<'"'>
		>,
		biscuit::seq<
			biscuit::chseq<'\''>,
			biscuit::star<
				biscuit::or_<
					biscuit::not_< biscuit::chset<'<','&','\''> >,
					typename detail::if_default<Reference<>, Reference_>::type
				>
			>,
			biscuit::chseq<'\''>
		>
	>
{ };


} } // namespace pstade::melon


#endif
