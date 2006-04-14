#ifndef PSTADE_BISCUIT_CONFIG_NULLARY_PARSER_HPP
#define PSTADE_BISCUIT_CONFIG_NULLARY_PARSER_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_BISCUIT_CFG_NULLARY_CLASS_TEMPLATE_PARSER)

	#define PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(t) \
		struct t \
	/**/
	
	#define PSTADE_BISCUIT_NULLARY_PARSER(t) \
		t \
	/**/
	
#else

	#include <boost/mpl/void.hpp>

	#define PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(t) \
		template< class = boost::mpl::void_ > \
		struct t \
	/**/

	#define PSTADE_BISCUIT_NULLARY_PARSER(t) \
		t<> \
	/**/

#endif


#endif
