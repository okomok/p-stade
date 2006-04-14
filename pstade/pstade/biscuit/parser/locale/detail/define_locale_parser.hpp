#ifndef PSTADE_BISCUIT_PARSER_LOCALE_DETAIL_DEFINE_LOCALE_PARSER_HPP
#define PSTADE_BISCUIT_PARSER_LOCALE_DETAIL_DEFINE_LOCALE_PARSER_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_CFG_NO_STD_LOCALE)


	#include <locale> // locale, isxxx
	#include <pstade/unused.hpp>
	#include "../../../config/nullary_parser.hpp"
	#include "../../../state/increment.hpp"
	#include "../../../state/is_end.hpp"


	#define PSTADE_BISCUIT_DEFINE_LOCALE_PARSER(name, pred) \
		namespace pstade { namespace biscuit { \
			\
			PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(name) \
			{ \
				template< class State, class UserState > \
				static bool parse(State& s, UserState& us) \
				{ \
					if (state_is_end(s)) \
						return false; \
					\
					if (!pred(*s.get_cur(), std::locale())) \
						return false; \
					\
					state_increment(s); \
					\
					pstade::unused(us); \
					return true; \
				} \
			}; \
			\
		} } \
	/**/


#else


	#define PSTADE_BISCUIT_DEFINE_LOCALE_PARSER(name, pred) \
	/**/


#endif // !defined(PSTADE_CFG_NO_STD_LOCALE)


#endif
