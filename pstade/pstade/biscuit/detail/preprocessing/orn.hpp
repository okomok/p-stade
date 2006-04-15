

#include <boost/preprocessor/cat.hpp>
#include "../../config/limit_parser_arity.hpp"

#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_typename or_
#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_limits PSTADE_BISCUIT_LIMIT_PARSER_ARITY
#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_param class
#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_arg P

#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_make_empty_body() \
	return false; \
/**/

#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_make_body(z, i, data) \
	if (BOOST_PP_CAT(P, i)::parse(s, us)) \
		return true; \
/**/

#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_body_footer \
	return false; \
/**/

#include "./numbered_parsers.hpp"
