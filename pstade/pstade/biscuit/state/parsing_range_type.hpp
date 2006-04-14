#ifndef PSTADE_BISCUIT_STATE_PARSING_RANGE_TYPE_HPP
#define PSTADE_BISCUIT_STATE_PARSING_RANGE_TYPE_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace biscuit {


template< class State >
struct state_parsing_range
{
	typedef typename State::parsing_range_type type;
};


} } // namespace pstade::biscuit


#endif
