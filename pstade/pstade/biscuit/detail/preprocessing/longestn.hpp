

#include <boost/preprocessor/cat.hpp>
#include "../../config/limit_parser_arity.hpp"

#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_typename longest
#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_limits PSTADE_BISCUIT_LIMIT_PARSER_ARITY
#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_param class
#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_arg P

#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_body_header \
    typedef typename boost::range_result_iterator<State>::type iter_t; \
    typedef typename boost::iterator_difference<iter_t>::type diff_t; \
    bool ret = false; \
    iter_t const marker = s.get_cur(); \
    diff_t d = 0; \
/**/

#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_make_empty_body() \
    return false; \
/**/

#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_make_body(z, i, data) \
    if (BOOST_PP_CAT(P, i)::parse(s, us)) \
    { \
        ret = true; \
        d = (std::max)(std::distance(marker, s.get_cur()), d); \
    } \
    s.set_cur(marker); \
/**/

#define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_body_footer \
    if (ret) \
    { \
        biscuit::state_advance(s, d); \
    } \
    return ret; \
/**/

#include "./numbered_parsers.hpp"
