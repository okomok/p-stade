#pragma once

namespace pstade { namespace biscuit {


template< class State >
struct state_class
{
	typedef typename State::state_class_type type;
};


} } // namespace pstade::biscuit
