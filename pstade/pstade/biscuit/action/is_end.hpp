#pragma once

#include <boost/range/end.hpp>

namespace pstade { namespace biscuit {


template< class State > inline
bool state_is_end(State const& s)
{
	return s.get_cur() == boost::end(s);
}


} } // namespace pstade::biscuit
