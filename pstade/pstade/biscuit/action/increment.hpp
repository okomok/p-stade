#pragma once

#include <boost/range/result_iterator.hpp>

namespace pstade { namespace biscuit {


template< class State > inline
State& state_increment(State& s)
{
	// Topic:
	//   It is surprising that VC7.1 can completely optimize this code.

	typedef typename boost::range_result_iterator<State>::type iter_t;
	iter_t cur = s.get_cur();
	++cur;
	s.set_cur(cur);
	return s;
}


} } // namespace pstade::biscuit
