#ifndef PSTADE_BISCUIT_STATE_IS_END_HPP
#define PSTADE_BISCUIT_STATE_IS_END_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/end.hpp>


namespace pstade { namespace biscuit {


template< class State > inline
bool state_is_end(State const& s)
{
	return s.get_cur() == boost::end(s);
}


} } // namespace pstade::biscuit


#endif
