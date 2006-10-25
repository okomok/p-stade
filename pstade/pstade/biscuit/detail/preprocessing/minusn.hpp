

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/if.hpp>
#include "../../config/limit_parser_arity.hpp"

#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_typename minus
#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_limits PSTADE_BISCUIT_LIMIT_PARSER_ARITY
#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_param class
#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_arg P

#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_make_empty_body() \
    return true; \
/**/

#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_body_header \
    state_cur_guard<State> gd(s); \
    \
    if (!P0::parse(s, us)) \
    { \
        return false; \
    } \
/**/

#define PSTADE_BISCUIT_make_body_if_0(i) \
    typedef typename oven::range_iterator<State>::type iter_t; \
    oven::iter_range<iter_t> rng(gd.marker(), s.get_cur()); \
/**/

#define PSTADE_BISCUIT_make_body_if_non0(i) \
    if (biscuit::state_match<BOOST_PP_CAT(P, i)>(rng, s, us)) \
    { \
        return false; \
    } \
/**/

#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_make_body(z, i, data) \
    BOOST_PP_IF(i, PSTADE_BISCUIT_make_body_if_non0(i), PSTADE_BISCUIT_make_body_if_0(i)) \
/**/

#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_body_footer \
    gd.dismiss(); \
    return true; \
/**/

#include "./numbered_parsers.hpp"

#undef PSTADE_BISCUIT_make_body_if_0
#undef PSTADE_BISCUIT_make_body_if_non0
