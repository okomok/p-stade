#pragma once

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
