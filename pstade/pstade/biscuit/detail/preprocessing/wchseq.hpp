#pragma once

#include "../../config/limit_parser_arity.hpp"

#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_header namespace pstade { namespace biscuit {
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_footer } }
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_typename wchseq
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_limits PSTADE_BISCUIT_LIMIT_PARSER_ARITY
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_param wchar_t
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg ch
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_default_arg 0

#include "./variadic_form.hpp"
