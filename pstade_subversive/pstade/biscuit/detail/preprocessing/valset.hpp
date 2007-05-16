

#include "../../config/limit_parser_arity.hpp"

#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_header namespace pstade { namespace biscuit {
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_footer } }
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_typename valset
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_limits PSTADE_BISCUIT_LIMIT_PARSER_ARITY

#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_param class
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg ValueFtor
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_default_arg boost::mpl::void_

#include "./variadic_form.hpp"
