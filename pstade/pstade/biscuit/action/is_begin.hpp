#pragma once

#include <boost/range/begin.hpp>

namespace pstade { namespace biscuit {


template< class State > inline
bool state_is_begin(State const& s)
{
	return s.get_cur() == boost::begin(s);
}


} } // namespace pstade::biscuit
