#ifndef PSTADE_BISCUIT_PARSER_ERROR_THROW_HPP
#define PSTADE_BISCUIT_PARSER_ERROR_THROW_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


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


#endif
