#pragma once

#include "../../config/limit_parser_arity.hpp"

#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_header namespace pstade { namespace biscuit {
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_footer } }
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_typename bchset
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_limits PSTADE_BISCUIT_LIMIT_PARSER_ARITY
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_param PSTADE_BISCUIT_CHARACTER_HOLDER_TYPE
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg ch
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_default_arg 0

#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_param_header class T
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg_header T

#include "./variadic_form_with_header.hpp"
