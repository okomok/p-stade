#pragma once

#include "./bchar.hpp"

namespace pstade { namespace biscuit {


template< wchar_t ch >
struct wchar :
	bchar< wchar_t, ch >
{ };


} } // namespace pstade::biscuit
