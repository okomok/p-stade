#ifndef PSTADE_MELON_CONTENT_HPP
#define PSTADE_MELON_CONTENT_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/opt.hpp>
#include <pstade/biscuit/parser/or.hpp>
#include <pstade/biscuit/parser/seq.hpp>
#include <pstade/biscuit/parser/star.hpp>
#include "./CDSect.hpp"
#include "./CharData.hpp"
#include "./Comment.hpp"
#include "./PI.hpp"
#include "./Reference.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
	class element_,
	class CharData_ = default_,
	class Reference_ = default_,
	class CDSect_ = default_,
	class PI_ = default_,
	class Comment_ = default_
>
struct content :
	biscuit::seq<
		biscuit::opt<
			typename detail::if_default<CharData<>, CharData_>::type
		>,
		biscuit::star<
			biscuit::seq<
				biscuit::or_<
					element_, // the magical recursion!
					typename detail::if_default<Reference<>, Reference_>::type,
					typename detail::if_default<CDSect<>, CDSect_>::type,
					typename detail::if_default<PI<>, PI_>::type,
					typename detail::if_default<Comment<>, Comment_>::type
				>,
				biscuit::opt<
					typename detail::if_default<CharData<>, CharData_>::type
				>
			>
		>
	>
{ };


} } // namespace pstade::melon


#endif
