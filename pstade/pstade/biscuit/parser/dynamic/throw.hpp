#pragma once

#include "./parser_error.hpp"

namespace pstade { namespace biscuit {


template< class Range, class InfoT >
inline void throw_(Range const& rng, InfoT& info)
{
	throw parser_error<Range, InfoT>(rng, info);
}

template< class Range, class InfoT >
inline void throw_(Range const& rng, InfoT const& info)
{
	throw parser_error<Range, InfoT>(rng, info);
}


} } // namespace pstade::biscuit
