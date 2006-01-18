#pragma once

namespace pstade { namespace biscuit {


template< class State >
struct state_parsing_range
{
	typedef typename State::parsing_range_type type;
};


} } // namespace pstade::biscuit
